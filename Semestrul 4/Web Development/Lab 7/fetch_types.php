<?php
// Include database connection
$conn = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');

// Fetch distinct severity values from logs table
$query = "SELECT DISTINCT logType FROM logs";
$result = mysqli_query($conn, $query);

// Convert result set to an array of severity values
$types = array();
while ($row = mysqli_fetch_assoc($result)) {
    $types[] = $row['logType'];
}

// Return JSON response with severity values
echo json_encode($types);
?>