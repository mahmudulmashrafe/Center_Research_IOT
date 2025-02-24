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

// Update status in the database
if (isset($_GET['status'])) {
    $status = ($_GET['status'] == 1) ? 1 : 0;
    $sql = "UPDATE distance_data SET status = $status ORDER BY id DESC LIMIT 1";

    if ($conn->query($sql) === TRUE) {
        echo "Status updated successfully.";
    } else {
        echo "Error: " . $conn->error;
    }
}

// Get the latest status
$result = $conn->query("SELECT status FROM distance_data ORDER BY id DESC LIMIT 1");
$currentStatus = $result->fetch_assoc()['status'] ?? 0;

$conn->close();
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LED Control</title>
</head>
<body>

<h2>LED Control</h2>

<p>Current Status: <strong><?php echo $currentStatus ? "ON" : "OFF"; ?></strong></p>

<!-- Buttons to Change Status -->
<form method="GET">
    <button type="submit" name="status" value="1">Turn ON LED</button>
    <button type="submit" name="status" value="0">Turn OFF LED</button>
</form>

</body>
</html>




