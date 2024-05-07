<?php
$con = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');

session_start();
if(isset($_POST['submit'])){
    $type = mysqli_real_escape_string($con, $_POST['type']);
    $severity = mysqli_real_escape_string($con, $_POST['severity']);
    $text = mysqli_real_escape_string($con, $_POST['text']);
    $author = $_SESSION['userID']; 
    
    
    $sqlComm = "INSERT INTO `logs`(`logType`, `logSeverity`, `logAuthor`, `logText`) 
    VALUES ('$type','$severity',$author,'$text')";
  
    $result = mysqli_query($con,$sqlComm);
    if($result){
        echo '<script>alert("Inserted successfully");</script>';
    } else {
        echo '<script>alert("Failed");</script>';
    }
};
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Add Log</title>
    <link rel="stylesheet" href="addStyle.css">
    <script>
        function validateForm() {
            var text = document.getElementById("text").value.trim();
            if (!isNaN(text)) { // Check if the input is not a number
                alert("Text must be a string, not a number.");
                return false; // Prevent form submission
            }
            return true; // Proceed with form submission
        }
    </script>
</head>
<body>
    <div id="add-form">
        <h3>Add Log</h3>
        <form id="log-form" method="POST" action="addLog.php" onsubmit="return validateForm()">
            <label for="type">Type:</label>
            <input type="text" id="type" name="type" required><br><br>
            <label for="severity">Severity:</label>
            <select id="severity" name="severity" required>
                <option value="debug">Debug</option>
                <option value="warning">Warning</option>
                <option value="notice">Notice</option>
                <option value="error">Error</option>
                <option value="critical">Critical</option>
            </select><br><br>
            <label for="text">Text:</label>
            <input type="text" id="text" name="text" required><br><br>
            <button class="buttonsAdd" type="submit" name="submit">Add</button>
        </form>
        <br>
        <button class="buttonsAdd" onclick="location.href='login.php'">Go to first page</button>
    </div>
</body>
</html>
