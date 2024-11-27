// Define the STAT pin connected to TP5100
const int statPin = 7;  // STAT pin connected to digital pin 7

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Set STAT pin as input with pull-up resistor
  pinMode(statPin, INPUT_PULLUP);

  Serial.println("TP5100 Charger Module Test");
}

void loop() {
  // Read the STAT pin status
  int statStatus = digitalRead(statPin);

  // Check charging status
  if (statStatus == LOW) {
    Serial.println("Charging in progress (STAT LOW)");
  } else if (statStatus == HIGH) {
    Serial.println("Charging complete or No battery (STAT HIGH)");
  } else {
    Serial.println("Unknown Status");
  }

  // Wait for a second before checking again
  delay(1000);
}

