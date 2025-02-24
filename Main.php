<?php
// Database credentials
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

// Retrieve the latest status
$result = $conn->query("SELECT status FROM distance_data ORDER BY id DESC LIMIT 1");
$latestStatus = ($result->num_rows > 0) ? $result->fetch_assoc()['status'] : 0; // Default to 0 if no records

// Handle Status Update (When Button Clicked)
if (isset($_GET['status'])) {
    $status = ($_GET['status'] == 1) ? 1 : 0;  // Set based on button click

    $sql = "INSERT INTO distance_data (distance, status) VALUES (NULL, ?)"; // Insert new record
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("i", $status);

    if ($stmt->execute()) {
        echo "Status updated successfully.";
    } else {
        echo "Error updating status: " . $conn->error;
    }
    $stmt->close();
}

// Handle Distance Data Insert (Keeps latest status)
if (isset($_GET['distance'])) {
    $distance = floatval($_GET['distance']);

    $sql = "INSERT INTO distance_data (distance, status) VALUES (?, ?)"; // Insert with latest status
    $stmt = $conn->prepare($sql);
    $stmt->bind_param("di", $distance, $latestStatus);

    if ($stmt->execute()) {
        echo "Data successfully inserted.";
    } else {
        echo "Error inserting data: " . $conn->error;
    }
    $stmt->close();
}

// Output latest status for ESP8266
echo $latestStatus;

$conn->close();
?>
