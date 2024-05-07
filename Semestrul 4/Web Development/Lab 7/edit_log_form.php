<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Edit Log</title>
    <link rel="stylesheet" href="editStyle.css"> <!-- Link to your external CSS file -->
  
</head>
<body>
    <h3>Edit Log</h3>
    <div id="edit-log-form">
        <form id="log-form" method="POST" action="edit_log.php" onsubmit="return validateForm()">
            <input type="hidden" id="edit-log-id" name="logId">
            <label for="edit-type">Type:</label>
            <input type="text" id="edit-type" name="type" required><br><br>
            <label for="edit-severity">Severity:</label>
            <select id="edit-severity" name="severity" required>
                <option value="debug">Debug</option>
                <option value="info">Info</option>
                <option value="warning">Warning</option>
                <option value="error">Error</option>
                <option value="critical">Critical</option>
            </select><br><br>
            <label for="edit-text">Text:</label>
            <input type="text" id="edit-text" name="text" required><br><br>
            <button type="submit" name="submit">Save</button>
            <br><br>
            <button class="cancelButton" type="button" onclick="cancelEdit()">Cancel</button>
        </form>
    </div>
    
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script>
        $(document).ready(function() {
            // Call function to populate the edit form with log details
            populateEditForm();
        });

        // Function to populate the edit form with log details
        function populateEditForm() {
            var urlParams = new URLSearchParams(window.location.search);
            var logId = urlParams.get('logId');
            $.ajax({
                url: 'fetch_log_details.php?id=' + logId, // PHP script to fetch log details
                type: 'GET',
                dataType: 'json',
                success: function(data) {
                    // Populate edit form fields with fetched log details
                    $('#edit-log-id').val(data.logID);
                    $('#edit-type').val(data.logType);
                    $('#edit-severity option[value="' + data.logSeverity + '"]').prop('selected', true);
                    $('#edit-text').val(data.logText);
                },
                error: function(xhr, status, error) {
                    console.error(xhr.responseText);
                }
            });
        }
        
        function validateForm() {
            var text = document.getElementById("edit-text").value.trim();
            if (!isNaN(text)) { // Check if the input is not a number
                alert("Text must be a string, not a number.");
                return false; // Prevent form submission
            }
            return true; // Proceed with form submission
        }
     
        // Function to cancel edit
        function cancelEdit() {
            // Implement cancel edit functionality if required
            window.location.href = "login.php";
        }
    </script>
</body>
</html>
