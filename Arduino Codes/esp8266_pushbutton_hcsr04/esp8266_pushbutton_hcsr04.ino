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

const int TRIG_PIN = D1;   
const int ECHO_PIN = D2;   
const int BUTTON_PIN = D5;  // Button connected to GPIO D5

void setup() {
    Serial.begin(115200);
    delay(1000);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Internal pull-up resistor for button

    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    static unsigned long lastMillis = 0;
    unsigned long currentMillis = millis();
    int buttonState = digitalRead(BUTTON_PIN);


     if (buttonState == LOW) {
      Serial.println("Button Pressed!!");
      takeAndSendReading();
    
     // Simple debounce - wait while button is still pressed
       while(digitalRead(BUTTON_PIN) == LOW) {
        delay(10);  // Small delay to avoid hogging the CPU
      }
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
    if (duration == 0) {
        return -1;
    }

    float distance = duration * 0.034 / 2;
    return distance;
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
