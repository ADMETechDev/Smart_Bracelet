// Pin definitions for DW01A
const int CHG_PIN = 2;  // Charge status pin
const int STBY_PIN = 3; // Standby/Discharge status pin

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the CHG and STBY pins as inputs with pull-up resistors
  pinMode(CHG_PIN, INPUT_PULLUP);
  pinMode(STBY_PIN, INPUT_PULLUP);

  // Initial message
  Serial.println("DW01A Battery Protection Module Test Initialized");
}

void loop() {
  // Read the status of the CHG and STBY pins
  int chgStatus = digitalRead(CHG_PIN);
  int stbyStatus = digitalRead(STBY_PIN);

  // Print the CHG status
  if (chgStatus == LOW) {
    Serial.println("Charging: ACTIVE (LOW) - Battery is Charging");
  } else {
    Serial.println("Charging: INACTIVE (HIGH) - Battery Not Charging");
  }

  // Print the STBY status
  if (stbyStatus == LOW) {
    Serial.println("Standby/Discharging: ACTIVE (LOW) - Battery is Discharging");
  } else {
    Serial.println("Standby/Discharging: INACTIVE (HIGH) - Battery Not Discharging");
  }

  // Add a short delay before the next read
  delay(1000);  // 1-second delay
}
