#include <SoftwareSerial.h>

#define RX_PIN 4  // RX pin for SIM28ML (to Arduino TX)
#define TX_PIN 3  // TX pin for SIM28ML (to Arduino RX)

SoftwareSerial gpsSerial(RX_PIN, TX_PIN);  // Set up software serial for GPS

String NMEA;
boolean newData = false;

void setup() {
  // Start the communication
  Serial.begin(9600);      // Communication with the computer (Serial Monitor)
  gpsSerial.begin(9600);   // Communication with the SIM28ML GPS module

  Serial.println("Initializing SIM28ML GPS module...");
}

void loop() {
  // Check if GPS data is available
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    if (c == '\n') {  // NMEA sentences end with a newline
      processNMEA(NMEA);
      NMEA = "";  // Clear the NMEA string for the next sentence
    } else {
      NMEA += c;  // Build up the NMEA sentence character by character
    }
  }
}

// Function to process and parse the NMEA sentence
void processNMEA(String nmeaSentence) {
  if (nmeaSentence.startsWith("$GPGGA")) {
    Serial.println("GPGGA Sentence Found!");
    parseGPGGA(nmeaSentence);
  }
}

// Function to parse GPGGA (Global Positioning System Fix Data)
void parseGPGGA(String nmeaSentence) {
  // Split the NMEA sentence by commas
  int indices[15];  // Array to store comma positions
  int indexCounter = 0;
  for (int i = 0; i < nmeaSentence.length(); i++) {
    if (nmeaSentence[i] == ',') {
      indices[indexCounter++] = i;
    }
  }

  // Extract Latitude and Longitude from the sentence
  String time = nmeaSentence.substring(indices[0] + 1, indices[1]);
  String latitude = nmeaSentence.substring(indices[1] + 1, indices[2]);
  String latDirection = nmeaSentence.substring(indices[2] + 1, indices[3]);
  String longitude = nmeaSentence.substring(indices[3] + 1, indices[4]);
  String lonDirection = nmeaSentence.substring(indices[4] + 1, indices[5]);
  String fixQuality = nmeaSentence.substring(indices[5] + 1, indices[6]);

  Serial.println("Time: " + time);
  Serial.println("Latitude: " + latitude + " " + latDirection);
  Serial.println("Longitude: " + longitude + " " + lonDirection);
  Serial.println("Fix Quality: " + fixQuality);
}
