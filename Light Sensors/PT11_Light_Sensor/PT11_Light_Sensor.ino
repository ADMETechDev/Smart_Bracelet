// Define the analog pin connected to the PT11 light sensor
const int lightSensorPin = A0;

void setup() {
  // Initialize the serial communication for debugging
  Serial.begin(9600);
  Serial.println("PT11 Light Sensor Test");
}

void loop() {
  // Read the analog value from the light sensor
  int lightLevel = analogRead(lightSensorPin);

  // Convert the analog reading to a voltage (optional)
  float voltage = lightLevel * (5.0 / 1023.0);

  // Print the light level and voltage to the Serial Monitor
  Serial.print("Light Level (Analog Value): ");
  Serial.print(lightLevel);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Delay for a short period before the next reading
  delay(500);
}
