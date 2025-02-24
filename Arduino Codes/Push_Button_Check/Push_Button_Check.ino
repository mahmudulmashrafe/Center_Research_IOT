// Simple push button test for NodeMCU
const int BUTTON_PIN = D5;  // Connect button between D5 and GND

void setup() {
  Serial.begin(115200);
  delay(1000);  // Give time for serial monitor to open
  
  // Set button pin as input with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);
     
  Serial.println("NodeMCU Button Test");
  Serial.println("Connect push button between D5 and GND");
  Serial.println("When you press the button, 'Hello World' will be printed");
  Serial.println("Waiting for button press...");
}

void loop() {
  // Read button state
  int buttonState = digitalRead(BUTTON_PIN);
  
  // When button is pressed (LOW because of pull-up resistor)
  if (buttonState == LOW) {
    Serial.println("Hello World");
    
    // Simple debounce - wait while button is still pressed
    while(digitalRead(BUTTON_PIN) == LOW) {
      delay(10);  // Small delay to avoid hogging the CPU
    }
    
    // Additional delay after button release to avoid bounce
    delay(50);
  }
}
