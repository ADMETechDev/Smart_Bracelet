// Define CHRG pin
const int chrgPin = 7;  // CHRG pin connected to digital pin 7

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Set CHRG pin as input with pull-up resistor
  pinMode(chrgPin, INPUT_PULLUP);

  Serial.println("TP4057 Charger Module Test");
}

void loop() {
  // Read the CHRG pin status
  int chrgStatus = digitalRead(chrgPin);

  // Check the charging status
  if (chrgStatus == LOW) {
    Serial.println("Charging in progress (CHRG LOW)");
  } else if (chrgStatus == HIGH) {
    Serial.println("Charging complete or No battery (CHRG HIGH)");
  } else {
    Serial.println("Unknown Status");
  }

  // Wait for a second before checking again
  delay(1000);
}
