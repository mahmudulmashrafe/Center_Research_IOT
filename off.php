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

// Find the latest row based on the largest id or latest timestamp
$sql = "SELECT id FROM distance_data ORDER BY id DESC LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Get the latest row's id
    $row = $result->fetch_assoc();
    $latest_id = $row['id'];

    // Update the status of the latest row to 0 (off)
    $update_sql = "UPDATE distance_data SET status = 0 WHERE id = $latest_id";

    if ($conn->query($update_sql) === TRUE) {
        echo "Status updated to OFF successfully";
    } else {
        echo "Error updating status: " . $conn->error;
    }
} else {
    echo "No rows found in the database.";
}

$conn->close();
?>
