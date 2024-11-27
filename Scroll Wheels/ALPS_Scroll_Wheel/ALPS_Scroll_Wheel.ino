// Define the pin connections for the rotary encoder
const int pinA = 2;  // CLK pin (A)
const int pinB = 3;  // DT pin (B)
const int buttonPin = 4;  // Switch button pin

int lastStateA = LOW;  // Last state of A pin
int currentStateA = LOW; // Current state of A pin
int counter = 0;        // Rotary encoder counter
bool buttonState = false; // Button state (pressed or not)

void setup() {
  pinMode(pinA, INPUT);  // Set pinA as input
  pinMode(pinB, INPUT);  // Set pinB as input
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin with internal pullup
  
  Serial.begin(9600);  // Initialize serial communication for output
  Serial.println("Rotary Encoder Test");
}

void loop() {
  // Read the current state of pin A
  currentStateA = digitalRead(pinA);
  
  // Check if there is a change in the encoder state
  if (currentStateA != lastStateA) {
    // If A has changed, check the direction based on the state of pin B
    if (digitalRead(pinB) != currentStateA) {
      counter++;  // Clockwise rotation
    } else {
      counter--;  // Counter-clockwise rotation
    }
    Serial.print("Counter: ");
    Serial.println(counter);
  }
  
  // Store the current state as the last state for the next loop
  lastStateA = currentStateA;
  
  // Read the button state
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == LOW) {  // Button is pressed (low state)
    Serial.println("Button Pressed");
    delay(200);  // Debounce delay
  }

  delay(10);  // Small delay to make the code run smoothly
}
