<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json");
header("Access-Control-Allow-Methods: POST, GET, PUT, DELETE");
header("Access-Control-Allow-Headers: Content-Type");

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "cattle_management_iot_server";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die(json_encode(["error" => "Connection failed: " . $conn->connect_error]));
}

// Handle GET request to fetch data
if ($_SERVER["REQUEST_METHOD"] == "GET") {
    $sql = "SELECT * FROM distance_data ORDER BY id DESC";
    $result = $conn->query($sql);
    $data = [];

    while ($row = $result->fetch_assoc()) {
        $data[] = $row;
    }

    echo json_encode($data);
}

// Handle POST request to insert new data
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $input = json_decode(file_get_contents("php://input"), true);
    $distance = $input["distance"];
    $status = $input["status"];

    $sql = "INSERT INTO distance_data (distance, status) VALUES ('$distance', '$status')";
    
    echo json_encode(["success" => $conn->query($sql)]);
}

// Handle PUT request to update data
if ($_SERVER["REQUEST_METHOD"] == "PUT") {
    $input = json_decode(file_get_contents("php://input"), true);
    $id = $input["id"];
    $distance = $input["distance"];
    $status = $input["status"];

    $sql = "UPDATE distance_data SET distance='$distance', status='$status' WHERE id='$id'";
    
    echo json_encode(["success" => $conn->query($sql)]);
}

// Handle DELETE request to delete data
if ($_SERVER["REQUEST_METHOD"] == "DELETE") {
    $input = json_decode(file_get_contents("php://input"), true);
    $id = $input["id"];

    $sql = "DELETE FROM distance_data WHERE id='$id'";
    
    echo json_encode(["success" => $conn->query($sql)]);
}

$conn->close();
?>
