#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


//Home
const char* ssid = "KingsMan";
const char* password = "#Iammhm#hw";
const char* serverName = "http://192.168.1.6/Cattle_Management_IOT/distance.php"; 

//UIU
// const char* ssid = "UIU-STUDENT";
// const char* password = "12345678";
// const char* serverName = "http://192.168.1.6/Cattle_Management_IOT/distance.php"; //Change it

const int TRIG_PIN = D1;   // GPIO pin connected to TRIG
const int ECHO_PIN = D2;   // GPIO pin connected to ECHO

void setup() {
    Serial.begin(115200);  // Initialize serial communication at 115200 baud rate
    delay(1000);           // Wait for Serial to initialize

    // Set the TRIG and ECHO pins
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Connect to Wi-Fi
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    // Wait until connected to WiFi
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Once connected, print the IP address
    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    float distance = getDistance();  // Get distance from the ultrasonic sensor

    // Print the distance
    if (distance != -1) {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");

        sendDataToServer(distance);  // Send data to the server
    } else {
        Serial.println("Sensor Timeout or Out of Range");
    }

    delay(10000);  // Wait for 1 second before taking the next reading
}

// Function to measure distance using the ultrasonic sensor
float getDistance() {
    // Send a pulse to the TRIG pin
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the pulse duration from the ECHO pin
    long duration = pulseIn(ECHO_PIN, HIGH);

    // If there was a timeout or error, return -1
    if (duration == 0) {
        return -1;
    }

    // Calculate the distance in centimeters
    float distance = duration * 0.034 / 2;  // Speed of sound is 0.034 cm/μs, divide by 2 to account for travel to and back
    return distance;
}

// Function to send distance data to the PHP script
void sendDataToServer(float distance) {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient wifiClient;  // Create a WiFiClient object
        HTTPClient http;

        String url = String(serverName) + "?distance=" + String(distance, 2);
        Serial.print("Sending request to: ");
        Serial.println(url);

        http.begin(wifiClient, url);  // Pass the WiFiClient object and URL to begin()
        int httpResponseCode = http.GET();  // Send the GET request

        if (httpResponseCode > 0) {
            String response = http.getString();  // Get the response from the server
            Serial.println("Server Response: " + response);
        } else {
            Serial.printf("HTTP Error: %d\n", httpResponseCode);
        }

        http.end();  // Close the HTTP connection
    } else {
        Serial.println("WiFi Disconnected!");
    }
}
