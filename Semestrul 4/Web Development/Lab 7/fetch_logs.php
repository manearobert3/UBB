<?php
session_start()
?>
<?php
// Include database connection
$conn = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');

// Pagination parameters
$page = isset($_GET['page']) && is_numeric($_GET['page']) ? $_GET['page'] : 1; // Current page number, default is 1
$pageSize = 4; // Number of records per page

// Filter parameter
$filter = isset($_GET['filter']) ? $_GET['filter'] : ''; // Filter option: '', 'all', 'user'
$type = $_GET['type'];
// Additional conditions for filtering
$conditions = '';


// Calculate offset
$offset = ($page - 1) * $pageSize;

// Fetch data from the database with pagination and filters
if ($type == 'user') {
    // Filter only user-specific logs
    $userID = $_SESSION['userID']; 
    $conditions = " WHERE logAuthor = '$userID'"; 
    $query = "SELECT * FROM logs $conditions LIMIT $offset, $pageSize";
}
else if ($type === 'all' || $type === 'nothing') {
    
    $query = "SELECT * FROM logs LIMIT $offset, $pageSize";
} else if($type ==='logSeverity' || $type ==='logType'){
    
    $filter = mysqli_real_escape_string($conn, $filter); // Sanitize the filter parameter
    if($type ==='logSeverity')
        $conditions = " WHERE logSeverity='$filter'";
            else 
        $conditions = " WHERE logType='$filter'";
    $query = "SELECT * FROM logs $conditions LIMIT $offset, $pageSize";
}
$query = "SELECT * FROM logs $conditions LIMIT $offset, $pageSize";
$result = mysqli_query($conn, $query);

// Convert result set to associative array
$logs = array();
while ($row = mysqli_fetch_assoc($result)) {
    $logs[] = $row;
}

// Get total number of logs (for calculating total pages)
$totalLogsQuery = "SELECT COUNT(*) AS totalLogs FROM logs $conditions";
$totalLogsResult = mysqli_query($conn, $totalLogsQuery);
$totalLogs = mysqli_fetch_assoc($totalLogsResult)['totalLogs'];

// Calculate total pages
$totalPages = ceil($totalLogs / $pageSize);

// Return JSON response with logs and total pages
echo json_encode(array('logs' => $logs, 'totalPages' => $totalPages));
?>
