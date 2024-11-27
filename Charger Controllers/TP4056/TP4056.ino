// Define the pin connections
const int stat1Pin = 7;  // STAT1 connected to digital pin 7
const int stat2Pin = 8;  // STAT2 connected to digital pin 8

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Set STAT pins as input
  pinMode(stat1Pin, INPUT);
  pinMode(stat2Pin, INPUT);

  Serial.println("TP4056 Charger Module Test");
}

void loop() {
  // Read the status pins
  int stat1 = digitalRead(stat1Pin);
  int stat2 = digitalRead(stat2Pin);

  // Check charging status
  if (stat1 == LOW && stat2 == HIGH) {
    Serial.println("Charging in progress (Red LED ON)");
  } else if (stat1 == HIGH && stat2 == LOW) {
    Serial.println("Charging complete (Green LED ON)");
  } else if (stat1 == HIGH && stat2 == HIGH) {
    Serial.println("No battery connected or not charging");
  } else {
    Serial.println("Error or unknown status");
  }

  // Wait for a second before checking again
  delay(1000);
}
