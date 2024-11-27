// Define the analog pin to read battery output voltage
const int batteryPin = A0;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  Serial.println("AP9101C Battery Protection Module Test");
}

void loop() {
  // Read the battery output voltage
  int batteryVoltageRaw = analogRead(batteryPin);
  
  // Convert the raw analog value to voltage (assuming 5V reference)
  float batteryVoltage = (batteryVoltageRaw * 5.0) / 1023.0;

  // Check if the battery output is active or protected
  if (batteryVoltage > 0.1) {
    Serial.print("Battery Output Active: ");
    Serial.print(batteryVoltage);
    Serial.println("V");
  } else {
    Serial.println("Battery Output Protected (No voltage detected)");
  }

  // Wait before reading again
  delay(1000);
}
