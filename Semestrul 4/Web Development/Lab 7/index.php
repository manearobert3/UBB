<?php
session_start();
$con = mysqli_connect('localhost', 'root', '', 'wdDB') or die('unable to connect to db');
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        body {
            font-family: Arial, sans-serif;
        }

        .login-container {
            width: 300px;
            margin: 0 auto;
            padding: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #f9f9f9;
        }

        .login-container h2 {
            margin-bottom: 20px;
            text-align: center;
        }

        .login-container label {
            display: block;
            margin-bottom: 10px;
        }

        .login-container input[type="text"],
        .login-container input[type="password"] {
            width: 100%;
            padding: 8px;
            margin-bottom: 15px;
            border: 1px solid #ccc;
            border-radius: 3px;
            box-sizing: border-box;
        }

        .login-container button {
            width: 100%;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            border-radius: 3px;
            cursor: pointer;
        }

        .login-container button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>


<div class="login-container">
    <h2>Login</h2>
    <form action="index.php" method="POST">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="password">Password:</label>
        <input type="password" id="password" name="password" required><br><br>
        <button type="submit" name="login">Login</button>
    </form>
</div>

<?php
if (isset($_POST['login'])) {
    $username = $_POST['username'];
    $password = $_POST['password'];

    $select = mysqli_query($con, "SELECT * FROM wdDB.users WHERE userName='$username' AND userPass='$password'");
    $row = mysqli_fetch_array($select);
    if (is_array($row)) {
        $_SESSION['userName'] = $row['userName'];
        $_SESSION['userPass'] = $row['userPass'];
        $_SESSION['userID']=$row['userID'];
        // Print the values from $row
        echo "<div>User ID: " . $row['userID'] . "</div>";
        echo "<div>Username: " . $row['userName'] . "</div>";
        // Add more fields as needed
    }
     else {
        echo '<script type = "text/javascript">';
        echo 'alert("Invalid Username or Password");';
        echo 'window.location.href="index.php"';
        echo '</script>';
        
    }
    echo "<div>Session: " . $_SESSION["userName"] . "</div>";
    if (isset($_SESSION["userName"])) {
        header("Location: login.php");
    }
}
?>
</body>
</html>
