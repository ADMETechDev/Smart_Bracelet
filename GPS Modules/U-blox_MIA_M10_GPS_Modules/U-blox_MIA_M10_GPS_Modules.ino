#include <HardwareSerial.h>

HardwareSerial GPS_Serial(1);  // Use UART1 for the GPS module

String NMEA;
boolean newData = false;

void setup() {
  // Start serial communication with the PC and the GPS module
  Serial.begin(115200);          // Serial Monitor communication
  GPS_Serial.begin(9600, SERIAL_8N1, 16, 17);  // GPS communication on pins 16 (RX), 17 (TX)

  Serial.println("Initializing u-blox MIA-M10 GPS module...");
}

void loop() {
  // Read data from the GPS module
  while (GPS_Serial.available()) {
    char c = GPS_Serial.read();
    if (c == '\n') {  // NMEA sentences end with a newline
      processNMEA(NMEA);  // Process the complete NMEA sentence
      NMEA = "";  // Clear the NMEA string for the next sentence
    } else {
      NMEA += c;  // Accumulate characters into the NMEA sentence
    }
  }
}

// Function to process and handle NMEA sentences
void processNMEA(String nmeaSentence) {
  if (nmeaSentence.startsWith("$GNGGA")) {  // GNGGA is the NMEA sentence for GPS fix data
    Serial.println("GNGGA Sentence Found!");
    parseGNGGA(nmeaSentence);
  }
}

// Function to parse GNGGA (Global Positioning System Fix Data)
void parseGNGGA(String nmeaSentence) {
  // Split the NMEA sentence by commas
  int indices[15];  // Array to store comma positions
  int indexCounter = 0;
  for (int i = 0; i < nmeaSentence.length(); i++) {
    if (nmeaSentence[i] == ',') {
      indices[indexCounter++] = i;
    }
  }

  // Extract Latitude, Longitude, Time, and Fix Quality
  String time = nmeaSentence.substring(indices[0] + 1, indices[1]);
  String latitude = nmeaSentence.substring(indices[1] + 1, indices[2]);
  String latDirection = nmeaSentence.substring(indices[2] + 1, indices[3]);
  String longitude = nmeaSentence.substring(indices[3] + 1, indices[4]);
  String lonDirection = nmeaSentence.substring(indices[4] + 1, indices[5]);
  String fixQuality = nmeaSentence.substring(indices[5] + 1, indices[6]);

  Serial.println("Time (UTC): " + time);
  Serial.println("Latitude: " + latitude + " " + latDirection);
  Serial.println("Longitude: " + longitude + " " + lonDirection);
  Serial.println("Fix Quality: " + fixQuality);
}
