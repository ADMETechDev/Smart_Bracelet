#include <Wire.h>

#define RF430_I2C_ADDRESS 0x28   // Default I²C address of RF430CL330H

void setup() {
  Serial.begin(9600);            // Initialize serial communication for debugging
  Wire.begin();                  // Initialize I²C communication

  delay(1000);                   // Give the RF430 time to initialize

  Serial.println("Initializing RF430...");

  // Check RF430 connection
  if (checkConnection()) {
    Serial.println("RF430CL330H Connected.");
  } else {
    Serial.println("Failed to connect to RF430CL330H.");
    while (1); // Stop if RF430 is not detected
  }

  // Write example data to RF430 memory
  writeDataToRF430(0xF868, "Hello NFC!");  // Write to SRAM at 0xF868
  delay(500);

  // Read data from RF430 memory
  String data = readDataFromRF430(0xF868, 10);  // Read 10 bytes from SRAM
  Serial.print("Read data from RF430: ");
  Serial.println(data);
}

void loop() {
  // Nothing to do here
}

// Function to check if RF430CL330H is connected
bool checkConnection() {
  Wire.beginTransmission(RF430_I2C_ADDRESS);
  return (Wire.endTransmission() == 0);
}

// Function to write data to RF430 memory (e.g., SRAM)
void writeDataToRF430(uint16_t address, String data) {
  Wire.beginTransmission(RF430_I2C_ADDRESS);
  Wire.write((address >> 8) & 0xFF);  // Send high byte of address
  Wire.write(address & 0xFF);         // Send low byte of address

  // Write data and pad with 0x00 if necessary
  for (int i = 0; i < data.length(); i++) {
    Wire.write(data[i]);              // Write each byte of the string
  }
  
  Wire.endTransmission();
  Serial.println("Data written to RF430.");
}

// Function to read data from RF430 memory (e.g., SRAM)
String readDataFromRF430(uint16_t address, int length) {
  Wire.beginTransmission(RF430_I2C_ADDRESS);
  Wire.write((address >> 8) & 0xFF);  // Send high byte of address
  Wire.write(address & 0xFF);         // Send low byte of address
  Wire.endTransmission();

  Wire.requestFrom(RF430_I2C_ADDRESS, length);  // Request 'length' bytes from RF430
  
  String result = "";
  while (Wire.available()) {
    char c = Wire.read();
    result += c;                      // Collect each byte
  }

  return result;
}
