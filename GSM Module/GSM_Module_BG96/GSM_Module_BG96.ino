#include <SoftwareSerial.h>

#define RX_PIN 7  // Define the RX pin for BG96 (to Arduino TX)
#define TX_PIN 8  // Define the TX pin for BG96 (to Arduino RX)

SoftwareSerial bg96Serial(RX_PIN, TX_PIN); // Create a software serial object

void setup() {
  // Start communication with the BG96 module
  Serial.begin(9600);        // Communication with the computer (Serial Monitor)
  bg96Serial.begin(115200);  // Communication with BG96
  
  Serial.println("Initializing Quectel BG96 GSM module...");

  delay(3000);  // Wait for the module to initialize

  // Send AT command to check if the module is responding
  sendATCommand("AT", "OK");

  // Check SIM card status
  sendATCommand("AT+CPIN?", "READY");

  // Set the device into text mode for SMS
  sendATCommand("AT+CMGF=1", "OK");

  // Set SMS service center address if required (optional)
  // sendATCommand("AT+CSCA=\"+1234567890\"", "OK");

  // Set preferred network to automatic (for LTE, 2G, 3G)
  sendATCommand("AT+QCFG=\"nwscanmode\",0", "OK");

  // Connect to the cellular network (check registration status)
  sendATCommand("AT+CREG?", "+CREG: 0,1");

  // Now send an SMS
  sendSMS("+1234567890", "Hello from Quectel BG96!");
}

void loop() {
  // Nothing to do in the loop
}

void sendSMS(String phoneNumber, String message) {
  // Send the AT command to start the SMS sending process
  bg96Serial.print("AT+CMGS=\"");
  bg96Serial.print(phoneNumber);
  bg96Serial.println("\"");
  delay(1000);

  // Send the SMS content
  bg96Serial.print(message);
  delay(1000);

  // End the message by sending a CTRL+Z character (ASCII 26)
  bg96Serial.write(26);
  delay(5000);  // Wait for the message to be sent

  Serial.println("SMS sent!");
}

void sendATCommand(String command, String expectedResponse) {
  bg96Serial.println(command);  // Send the command to the BG96 module
  delay(1000);  // Give the module time to respond

  String response = "";
  while (bg96Serial.available()) {
    char c = bg96Serial.read();
    response += c;
  }

  Serial.println("AT Command: " + command);
  Serial.println("Response: " + response);

  // Check if the expected response is in the module's reply
  if (response.indexOf(expectedResponse) != -1) {
    Serial.println("Command successful: " + command);
  } else {
    Serial.println("Command failed: " + command);
  }
}
