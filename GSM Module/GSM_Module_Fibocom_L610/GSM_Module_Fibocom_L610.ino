#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(2, 3); // RX (to GSM TX), TX (to GSM RX)

void setup() {
  Serial.begin(9600);          // Initialize the serial monitor for debugging
  gsmSerial.begin(9600);       // Initialize GSM module serial connection
  
  delay(1000);                 // Give some time for the module to initialize

  Serial.println("Making a phone call...");
  makeCall("1234567890");      // Replace with the phone number to call
}

void loop() {
  // Handle any incoming data from the GSM module
  if (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }

  // Handle user input from the serial monitor
  if (Serial.available()) {
    gsmSerial.write(Serial.read());
  }
}

void makeCall(String phoneNumber) {
  gsmSerial.println("AT");                  // AT command to check communication
  delay(1000);
  
  gsmSerial.print("ATD");                   // ATD command to dial a number
  gsmSerial.print(phoneNumber);             // Append the phone number to dial
  gsmSerial.println(";");                   // End command with semicolon
  delay(1000);

  Serial.println("Calling...");
}

void endCall() {
  gsmSerial.println("ATH");                 // ATH command to hang up
  delay(1000);

  Serial.println("Call ended");
}
