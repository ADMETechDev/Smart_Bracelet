// Pin definitions for the rotary encoder
const int pinA = 2;  // CLK (A) pin
const int pinB = 3;  // DT (B) pin
const int buttonPin = 4;  // Button press pin (if present)

int lastStateA = LOW;  // Last state of pin A
int currentStateA = LOW; // Current state of pin A
int counter = 0;  // Counter for rotary movement
bool buttonState = false; // Button state (pressed or not)

void setup() {
  // Set the rotary encoder pins as inputs
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up for the button pin
  
  // Start serial communication
  Serial.begin(9600);
  Serial.println("Rotary Encoder Test - SRBE Scroll Wheel");
}

void loop() {
  // Read the current state of pin A
  currentStateA = digitalRead(pinA);

  // Detect if there is a change in the A pin state
  if (currentStateA != lastStateA) {
    // If pin A changes, check pin B to determine direction
    if (digitalRead(pinB) != currentStateA) {
      counter++;  // Clockwise rotation
    } else {
      counter--;  // Counter-clockwise rotation
    }

    // Print the updated counter (steps of rotation)
    Serial.print("Counter: ");
    Serial.println(counter);
  }

  // Update the lastStateA to the current state for the next loop
  lastStateA = currentStateA;

  // Check if the button is pressed (if present)
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {  // Button is pressed (LOW due to pull-up)
    Serial.println("Button Pressed");
    delay(200);  // Debounce delay to avoid multiple presses
  }

  delay(10);  // Small delay for smooth operation
}

