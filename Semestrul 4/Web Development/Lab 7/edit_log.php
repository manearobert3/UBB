<?php
session_start();
?>
<?php
// Include database connection
$conn = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');

// Check if form data is submitted via POST
 
    if(isset($_POST['logId']) && isset($_POST['type']) && isset($_POST['severity']) && isset($_POST['text'])) {
        // Sanitize input data to prevent SQL injection
        $logId = mysqli_real_escape_string($conn, $_POST['logId']);
        $type = mysqli_real_escape_string($conn, $_POST['type']);
        $severity = mysqli_real_escape_string($conn, $_POST['severity']);
        $text = mysqli_real_escape_string($conn, $_POST['text']);
        $query1 = "SELECT logAuthor FROM logs WHERE logID = $logId";
        $resultID = mysqli_query($conn, $query1);
        // Prepare SQL query to update log entry
        if($resultID) {
            // Fetch the result as an associative array
            $row = mysqli_fetch_assoc($resultID);
            // Get the log author value
            $logAuthor = $row['logAuthor'];
            
            // Check if the logged-in user is the author of the log
            if ($_SESSION["userID"] == $logAuthor) {
                $sql = "UPDATE logs SET logType = '$type', logSeverity = '$severity', logText = '$text' WHERE logID = $logId";
                $result = mysqli_query($conn, $sql);
        // Check if query executed successfully
        if($result) {
            // Return success response
            echo '<script>alert("Updated successfully");window.location.href = "login.php";</script>';
        } else {
            // If query failed, return an error response
            echo '<script>alert("Failed to update log entry");window.location.href = "login.php";</script>'; 
        }
    }else{
        echo '<script>alert("You are not the owner of this log");window.location.href = "login.php";</script>';
        }
    } else {
    // If form data is not submitted, return an error response
    echo '<script>alert("Form data not provided");window.location.href = "login.php";</script>';
    
    }
}

?>
