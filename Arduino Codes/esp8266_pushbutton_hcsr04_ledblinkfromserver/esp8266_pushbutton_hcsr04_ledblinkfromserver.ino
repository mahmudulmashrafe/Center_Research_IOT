#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

// WiFi Credentials
//const char* ssid = "KingsMan";
//const char* password = "#Iammhm#hw";
//const char* serverName = "http://192.168.1.6/Cattle_Management_IOT/distance.php"; 


//UIU
 const char* ssid = "UIU-STUDENT";
 const char* password = "12345678";
 const char* serverName = "http://10.15.18.188/Cattle_Management_IOT/distance.php"; //Change it

ESP8266WebServer server(80); // Start a web server on port 80

// Ultrasonic Sensor Pins
const int TRIG_PIN = D1;   
const int ECHO_PIN = D2;   
const int BUTTON_PIN = D5;  // Button to manually trigger measurement

// LED Pins
const int GREEN_LED = D6;   // Green LED (distance ≤ 10cm)
const int RED_LED = D7;     // Red LED (distance > 10cm)
const int BLINK_LED = D4;   // LED controlled via PHP button



void handleBlink() {
    digitalWrite(BLINK_LED, HIGH);
    delay(500);
    digitalWrite(BLINK_LED, LOW);
    server.send(200, "text/plain", "LED Blinking!");
}


void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLINK_LED, OUTPUT);
    digitalWrite(BLINK_LED, LOW);

    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    // Handle LED Blink Request from PHP
    server.on("/blink_led", handleBlink);
    server.begin();
}

void loop() {
    server.handleClient();  // Listen for PHP requests

    static unsigned long lastMillis = 0;
    unsigned long currentMillis = millis();
    int buttonState = digitalRead(BUTTON_PIN);

    if (buttonState == LOW) {
        Serial.println("Button Pressed!!");
        takeAndSendReading();

        while (digitalRead(BUTTON_PIN) == LOW) { delay(10); }
        delay(50);
    }

    if (currentMillis - lastMillis >= 10000) {
        lastMillis = currentMillis;
        Serial.println("Taking scheduled reading...");
        takeAndSendReading();
    }
}

void takeAndSendReading() {
    float distance = getDistance();
    if (distance != -1) {
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");

        controlLEDs(distance);
        sendDataToServer(distance);
    } else {
        Serial.println("Sensor Timeout or Out of Range");
    }
}

float getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH);
    if (duration == 0) return -1; // No response, sensor out of range

    float distance = duration * 0.034 / 2;
    return distance;
}

void controlLEDs(float distance) {
    if (distance <= 10) {
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(RED_LED, LOW);
        delay(500);
        digitalWrite(GREEN_LED, LOW);
    } else {
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        delay(500);
        digitalWrite(RED_LED, LOW);
    }
}

void blinkLED() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(BLINK_LED, HIGH);
        delay(300);
        digitalWrite(BLINK_LED, LOW);
        delay(300);
    }
}

void sendDataToServer(float distance) {
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient wifiClient;
        HTTPClient http;

        String url = String(serverName) + "?distance=" + String(distance, 2);
        Serial.print("Sending request to: ");
        Serial.println(url);

        http.begin(wifiClient, url);
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Server Response: " + response);
        } else {
            Serial.printf("HTTP Error: %d\n", httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected!");
    }
}
