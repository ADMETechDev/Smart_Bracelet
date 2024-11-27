#include <SPI.h>

// Pin Definitions
const int CS_PIN = 10;    // Chip Select pin for ADS7843
const int PENIRQ_PIN = 2; // Optional: Pen interrupt pin

void setup() {
  // Initialize SPI communication
  SPI.begin();

  // Set CS and PENIRQ pins
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Deselect the ADS7843

  pinMode(PENIRQ_PIN, INPUT_PULLUP); // Pen interrupt

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("ADS7843 Touch Sensor Test");
}

void loop() {
  // Check if the screen is touched
  if (digitalRead(PENIRQ_PIN) == LOW) {
    // Read X and Y coordinates
    int x = readTouchData(0x90); // Command to read X-coordinate
    int y = readTouchData(0xD0); // Command to read Y-coordinate

    // Print X and Y coordinates
    Serial.print("X: ");
    Serial.print(x);
    Serial.print(", Y: ");
    Serial.println(y);

    delay(100); // Short delay for stability
  } else {
    Serial.println("No touch detected");
    delay(500); // Check again after 500ms
  }
}

// Function to read touch data from ADS7843
int readTouchData(byte command) {
  digitalWrite(CS_PIN, LOW); // Select the ADS7843

  SPI.transfer(command); // Send command to read data
  int highByte = SPI.transfer(0x00); // Read high byte of data
  int lowByte = SPI.transfer(0x00);  // Read low byte of data

  digitalWrite(CS_PIN, HIGH); // Deselect the ADS7843

  // Combine high and low bytes to get a 12-bit result
  int result = ((highByte << 8) | lowByte) >> 3;

  return result;
}
