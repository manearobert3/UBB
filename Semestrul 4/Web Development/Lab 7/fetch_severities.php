<?php
// Include database connection
$conn = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');

// Fetch distinct severity values from logs table
$query = "SELECT DISTINCT logSeverity FROM logs";
$result = mysqli_query($conn, $query);

// Convert result set to an array of severity values
$severities = array();
while ($row = mysqli_fetch_assoc($result)) {
    $severities[] = $row['logSeverity'];
}

// Return JSON response with severity values
echo json_encode($severities);
?>