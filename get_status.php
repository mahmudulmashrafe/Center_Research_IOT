<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "cattle_management_iot_server";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Handle button click
if (isset($_GET['status'])) {
    $new_status = ($_GET['status'] == "1") ? 1 : 0;
    $conn->query("UPDATE distance_data SET status = $new_status ORDER BY id DESC LIMIT 1");
}

// Fetch current status
$result = $conn->query("SELECT status FROM distance_data ORDER BY id DESC LIMIT 1");
$status = $result->fetch_assoc()['status'] ?? 0;
$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED Control</title>
    <style>
        body { font-family: Arial, sans-serif; text-align: center; padding: 20px; }
        .status { font-size: 24px; font-weight: bold; margin: 20px 0; }
        .on { color: green; }
        .off { color: red; }
        button { padding: 10px 20px; font-size: 16px; cursor: pointer; }
    </style>
</head>
<body>

<h2>LED Control</h2>
<p class="status <?php echo ($status == 1) ? 'on' : 'off'; ?>">
    Current Status: <strong><?php echo ($status == 1) ? 'ON' : 'OFF'; ?></strong>
</p>

<form method="GET">
    <button type="submit" name="status" value="1" style="background: green; color: white;">Turn ON</button>
    <button type="submit" name="status" value="0" style="background: red; color: white;">Turn OFF</button>
</form>

</body>
</html>
