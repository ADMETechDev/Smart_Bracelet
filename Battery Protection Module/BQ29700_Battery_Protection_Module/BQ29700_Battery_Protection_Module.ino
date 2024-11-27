// Define the analog input pin where the voltage divider is connected
#define BATTERY_VOLTAGE_PIN 34

// Constants for converting ADC value to actual battery voltage
const float ADC_MAX_VOLTAGE = 3.3;  // Max voltage the ESP32 ADC can read (3.3V)
const int ADC_RESOLUTION = 4095;    // 12-bit ADC (0-4095)
const float VOLTAGE_DIVIDER_RATIO = 2.0;  // Voltage is divided by 2 in the circuit

void setup() {
  Serial.begin(115200);  // Initialize serial communication
}

void loop() {
  // Read the ADC value (battery voltage)
  int adcValue = analogRead(BATTERY_VOLTAGE_PIN);

  // Convert the ADC value to actual voltage
  float batteryVoltage = (adcValue * ADC_MAX_VOLTAGE / ADC_RESOLUTION) * VOLTAGE_DIVIDER_RATIO;

  // Print the battery voltage to the Serial Monitor
  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage);
  Serial.println(" V");

  // Check if the battery voltage is low
  if (batteryVoltage < 3.0) {
    Serial.println("Warning: Battery voltage is low!");
    // Perform low-battery actions (e.g., shut down safely, send a warning)
  }

  delay(1000);  // Delay for 1 second before the next reading
}
