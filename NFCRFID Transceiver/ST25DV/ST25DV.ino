#include <Wire.h>

#define ST25DV_I2C_ADDRESS 0x53  // Default I²C address of ST25DV

void setup() {
  Serial.begin(9600);            // Start serial communication for debugging
  Wire.begin();                  // Start I²C communication

  delay(1000);                   // Give the ST25DV time to initialize

  Serial.println("Initializing ST25DV...");

  // Check ST25DV Connection
  if (checkConnection()) {
    Serial.println("ST25DV Connected.");
  } else {
    Serial.println("Failed to connect to ST25DV.");
    while (1); // Stop if ST25DV is not detected
  }

  // Write data to a memory block in ST25DV
  writeDataToST25DV(0x00, "Hello ST25DV!"); // Write to block 0x00
  delay(500);

  // Read data from a memory block in ST25DV
  String data = readDataFromST25DV(0x00);   // Read from block 0x00
  Serial.print("Read data from ST25DV: ");
  Serial.println(data);
}

void loop() {
  // Nothing to do here
}

// Function to check if ST25DV is connected
bool checkConnection() {
  Wire.beginTransmission(ST25DV_I2C_ADDRESS);
  return (Wire.endTransmission() == 0);
}

// Function to write data to ST25DV memory
void writeDataToST25DV(uint8_t block, String data) {
  Wire.beginTransmission(ST25DV_I2C_ADDRESS);
  Wire.write(block);   // Set memory block to write
  
  // Write data and pad it if necessary
  for (int i = 0; i < 16; i++) {
    if (i < data.length()) {
      Wire.write(data[i]);   // Write data byte by byte
    } else {
      Wire.write(0x00);      // Pad with zeros if data is shorter than 16 bytes
    }
  }
  
  Wire.endTransmission();
  Serial.println("Data written to ST25DV.");
}

// Function to read data from ST25DV memory
String readDataFromST25DV(uint8_t block) {
  Wire.beginTransmission(ST25DV_I2C_ADDRESS);
  Wire.write(block);   // Set memory block to read
  Wire.endTransmission();

  Wire.requestFrom(ST25DV_I2C_ADDRESS, 16); // Request 16 bytes of data
  
  String result = "";
  while (Wire.available()) {
    char c = Wire.read();
    if (c != 0x00) {
      result += c;     // Append non-null bytes to the result
    }
  }
  
  return result;
}
