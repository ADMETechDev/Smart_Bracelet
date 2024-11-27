#include <Wire.h>

#define NTAG_I2C_ADDRESS 0x55  // Default I2C address of NTAG I2C Plus

void setup() {
  Serial.begin(9600);         // Initialize serial communication
  Wire.begin();               // Initialize I2C communication

  delay(1000);                // Give the NTAG I2C time to initialize

  Serial.println("Initializing NTAG I2C...");

  // Check NTAG I2C Connection
  if (checkConnection()) {
    Serial.println("NTAG I2C Connected.");
  } else {
    Serial.println("Failed to connect to NTAG I2C.");
    while (1); // Stop if NTAG is not detected
  }

  // Write example data to NTAG I2C memory
  writeDataToNTAG(0x04, "Hello NFC!");  // Write to page 4 of NTAG memory
  delay(500);

  // Read data from NTAG I2C memory
  String data = readDataFromNTAG(0x04);  // Read from page 4 of NTAG memory
  Serial.print("Read data from NTAG: ");
  Serial.println(data);
}

void loop() {
  // Nothing to do here
}

// Function to check if NTAG I2C Plus is connected
bool checkConnection() {
  Wire.beginTransmission(NTAG_I2C_ADDRESS);
  return (Wire.endTransmission() == 0);
}

// Function to write data to NTAG memory
void writeDataToNTAG(uint8_t page, String data) {
  Wire.beginTransmission(NTAG_I2C_ADDRESS);
  Wire.write(page);    // Set the memory page to write

  // Pad the data with 0x00 to ensure it's 16 bytes (4 bytes per page)
  for (int i = 0; i < 16; i++) {
    if (i < data.length()) {
      Wire.write(data[i]);   // Write character data byte by byte
    } else {
      Wire.write(0x00);      // Fill remaining space with zeros
    }
  }

  Wire.endTransmission();
  Serial.println("Data written to NTAG.");
}

// Function to read data from NTAG memory
String readDataFromNTAG(uint8_t page) {
  Wire.beginTransmission(NTAG_I2C_ADDRESS);
  Wire.write(page);    // Set the memory page to read
  Wire.endTransmission();

  Wire.requestFrom(NTAG_I2C_ADDRESS, 16);  // Request 16 bytes (4 bytes per page, NTAG has 4 pages)
  
  String result = "";
  while (Wire.available()) {
    char c = Wire.read();
    if (c != 0x00) {
      result += c;     // Append non-null bytes to result
    }
  }
  return result;
}
