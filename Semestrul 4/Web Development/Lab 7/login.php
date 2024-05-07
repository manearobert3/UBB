<?php session_start(); ?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="style.css">
    <title>Document</title>
</head>
<body>
    <h2> Welcome user: <?php echo $_SESSION['userName']; ?></h2>
    <div class="button-links">
    <a href="logout.php" >Logout</a>
</br>
</br>
    <a href="addLog.php" >Add</a>
</div>
</br>
    <label for="severity-filter">Filter by Severity:</label>
    <select id="severity-filter" onchange="fetchData('logSeverity')">
        <option value=""></option>
    </select>
    <label for="type-filter">Filter by Type:</label>
    <select id="type-filter" onchange="fetchData('logType')">
        <option value=""></option>
    </select>
</br>
</br>
    <!-- Dropdown button -->

    <div class="dropdown">
        <div class="dropdown-content">
            <a href="#" onclick="fetchData('all')">All Logs</a>
            <a href="#" onclick="fetchData('user')">User Logs</a>
        </div>
    </div>

    <!-- Table to display logs -->
    <table id="log-table">
        <thead>
            <tr>
                <th>Type</th>
                <th>Severity</th>
                <th>Date of Creation</th>
                <th>Text</th>
                <th>Action</th>
            </tr>
        </thead>
        <tbody>
            <!-- Table rows will be added dynamically using JavaScript -->
        </tbody>
    </table>
    <div id="pagination-container">
        <!-- Previous and next buttons will be added dynamically using JavaScript -->
     
    </div>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

    <script>
        var lastFilter='';
        var currentPage = 1; // Initialize current page
        function populateSeverityOptions() {
            $.ajax({
                url: 'fetch_severities.php', // PHP script to fetch severity values
                type: 'GET',
                dataType: 'json',
                success: function(data) {
                    // Populate select element with severity options
                    var selectElement = $('#severity-filter');
                    $.each(data, function(index, severity) {
                        selectElement.append($('<option>').text(severity).attr('value', severity));
                    });
                },
                error: function(xhr, status, error) {
                    console.error(xhr.responseText);
                }
            });
        }
        function populateTypeOptions() {
            
            $.ajax({
                url: 'fetch_types.php', // PHP script to fetch severity values
                type: 'GET',
                dataType: 'json',
                success: function(data) {
                    // Populate select element with severity options
                    var selectElement = $('#type-filter');
                    $.each(data, function(index, type) {
                        selectElement.append($('<option>').text(type).attr('value', type));
                    });
                },
                error: function(xhr, status, error) {
                    console.error(xhr.responseText);
                }
            });
        }
        
    
        // Function to fetch data from the server with pagination and filters
        function fetchData(filterInput) {
            var filter;
            if(lastFilter!= filterInput){
                currentPage = 1; // Reset current page to 1 when applying a filter
    
            }
            lastFilter=filterInput;
           
            if (filterInput === 'logSeverity') {
                filter = $('#severity-filter').val(); // Get selected severity filter
            } else {
                filter = $('#type-filter').val();
            }
            $.ajax({
                url: 'fetch_logs.php', // PHP script to fetch data
                type: 'GET',
                data: { 
                    page: currentPage,
                    filter: filter,
                    type: filterInput// Pass filter option
                },
                dataType: 'json',
                success: function(data) {
                    // Populate table with fetched data
                    populateTable(data.logs);
                    updatePagination(data.totalPages);
                    
                },
                error: function(xhr, status, error) {
                    console.error(xhr.responseText);
                }
            });
        }
        var totalPages = 0; // Define totalPages globally


        // Function to populate the table with data
        function populateTable(logs) {
            var tableBody = $('#log-table tbody');
            tableBody.empty(); // Clear existing rows
            
            // Iterate over each log entry and add a row to the table
            $.each(logs, function(index, log) {
                var row = $('<tr>');
                row.append($('<td>').text(log.logType));
                row.append($('<td>').text(log.logSeverity));
                row.append($('<td>').text(log.logDate));
                row.append($('<td>').text(log.logText));
                row.append($('<td>').html('<button onclick="editLog(' + log.logID + ')">Edit</button> <button onclick="deleteLog(' + log.logID + ')">Delete</button>'));
                tableBody.append(row);
            });
        }

        $(document).ready(function() {
            populateSeverityOptions();
            populateTypeOptions();
        });
        function updatePagination(totalPagesValue) {
            totalPages = totalPagesValue; // Update totalPages globally
            
            var paginationContainer = $('#pagination-container');
            paginationContainer.empty(); // Clear existing pagination links
            
            // Create previous button
            var previousButton = $('<button>').text('Previous').addClass('page-link');
            previousButton.click(function() {
                fetchPreviousPage(); // Fetch data for the previous page
            });
            paginationContainer.append(previousButton);

            // Create next button
            var nextButton = $('<button>').text('Next').addClass('page-link');
            nextButton.click(function() {
                fetchNextPage(); // Fetch data for the next page
            });
            paginationContainer.append(nextButton);
        }


        function editLog(id) {
            // Implement edit functionality
            $.ajax({
        url: 'fetch_log_details.php?id=' + id, // PHP script to fetch log details
        type: 'GET',
        dataType: 'json',
        success: function(data) {
            // Populate edit form fields with fetched log details
            console.log(data); 
            $('#edit-log-id').val(data.logID);
            $('#edit-type').val(data.logType);
            $('#edit-severity').val(data.logSeverity);
            $('#edit-text').val(data.logText);
            
            // Redirect to the edit form page
            var logId = data.logID;
    window.location.href = 'edit_log_form.php?logId=' + logId;
        },
        error: function(xhr, status, error) {
            console.error(xhr.responseText);
        }});
        }

        /// Function to handle delete log
        function deleteLog(id) {
    console.log("Deleting log with ID:", id); // Log the ID parameter
    $.ajax({
        url: 'delete_log.php',
        type: 'POST',
        data: { id: id }, // Include the log ID in the POST data
        dataType: 'text', // Change the data type to 'text'
        success: function(response) {
            console.log("Delete log response:", response); // Log the response
            fetchData(lastFilter); // Fetch updated data after successful deletion
            alert("Delete log response: " + response); 
        },
        error: function(xhr, status, error) {
            console.error(xhr.responseText);
            alert("An error occurred while deleting the log");
        }
    });
}

// Function to fetch data for the previous page
function fetchPreviousPage() {
    if (currentPage > 1) {
        currentPage--; // Decrement current page number
        fetchData(lastFilter); // Fetch data for the previous page
    }
}

// Function to fetch data for the next page
function fetchNextPage() {
    if (currentPage < totalPages) {
        currentPage++; // Increment current page number
        fetchData(lastFilter); // Fetch data for the next page
    }
}
       
// Function to submit the edit form via AJAX
    

    </script>
</body>
</html>
