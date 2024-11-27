#include <Wire.h>

#define TTP229_ADDR 0x57  // Default I2C address for TTP229 module

void setup() {
  Serial.begin(115200);    // Initialize serial communication with the PC
  Wire.begin(21, 22);      // Initialize I2C with SDA on GPIO 21 and SCL on GPIO 22

  Serial.println("TTP229 Touch Digitizer Test");
}

void loop() {
  // Request data from the TTP229 module
  Wire.beginTransmission(TTP229_ADDR);
  Wire.write(0x00);  // Request data from register 0x00 (status register)
  Wire.endTransmission();

  Wire.requestFrom(TTP229_ADDR, 2);  // Request 2 bytes of data

  if (Wire.available() == 2) {
    uint8_t dataHigh = Wire.read();  // Read the high byte
    uint8_t dataLow = Wire.read();   // Read the low byte
    uint16_t touchData = (dataHigh << 8) | dataLow;  // Combine high and low bytes

    Serial.print("Touch Data: ");
    Serial.println(touchData, HEX);  // Print touch data in hexadecimal

    // Print status of each touch key
    for (int i = 0; i < 16; i++) {
      if (touchData & (1 << i)) {
        Serial.print("Key ");
        Serial.print(i + 1);
        Serial.println(" touched");
      }
    }
  } else {
    Serial.println("Failed to read from TTP229 module");
  }

  delay(100);  // Delay to prevent flooding the serial output
}
