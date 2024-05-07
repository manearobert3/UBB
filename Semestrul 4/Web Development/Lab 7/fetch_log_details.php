<?php
// fetch_log_details.php

// Include database connection
$conn = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');


// Check if log ID is provided in the request
if(isset($_GET['id'])) {
    $logId = $_GET['id'];

    // Prepare SQL query to fetch log details by ID
    $sql = "SELECT * FROM logs WHERE logID = '$logId'";
    
    // Execute the query
    $result = mysqli_query($conn, $sql);
    
    // Check if query executed successfully
    if($result) {
        // Fetch log details as an associative array
        $logDetails = mysqli_fetch_assoc($result);
        
        // Return log details as JSON response
        echo json_encode($logDetails);
    } else {
        // If query failed, return an error response
        echo json_encode(['error' => 'Failed to fetch log details']);
    }
} else {
    // If log ID is not provided in the request, return an error response
    echo json_encode(['error' => 'Log ID not provided']);
}
?>
