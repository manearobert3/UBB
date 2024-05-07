<?php
session_start();

// Include database connection
$conn = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');

// Check if the ID parameter is set
if(isset($_POST['id'])) {
    // Sanitize the input to prevent SQL injection
    $id = mysqli_real_escape_string($conn, $_POST['id']);
    
    // Query to get the log author
    $query1 = "SELECT logAuthor FROM logs WHERE logID = $id";
    $resultID = mysqli_query($conn, $query1);
    
    // Check if the query executed successfully
    if($resultID) {
        // Fetch the result as an associative array
        $row = mysqli_fetch_assoc($resultID);
        // Get the log author value
        $logAuthor = $row['logAuthor'];
        
        // Check if the logged-in user is the author of the log
        if ($_SESSION["userID"] == $logAuthor) {
            // Delete the record from the database
            $query2 = "DELETE FROM logs WHERE logID = $id";
            $result = mysqli_query($conn, $query2);
            
            if($result) {
                // Deletion successful
                echo "Deleted succesfully";
            } else {
                // Error occurred during deletion
                echo "Error: Unable to delete log - " . mysqli_error($conn);
            }
        } else {
            // User is not authorized to delete this log
            echo "Error: You are not authorized to delete this log";
        }
    } else {
        // Error fetching log author
        echo "Error: Unable to fetch log author - " . mysqli_error($conn);
    }
} else {
    // ID parameter not set
    echo "Error: ID parameter missing";
}
?>