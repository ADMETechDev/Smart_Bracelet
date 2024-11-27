const int controlPin = 9; // PWM pin connected to the control input of APK2127

void setup() {
  pinMode(controlPin, OUTPUT); // Set the control pin as an output
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  // Gradually increase the brightness (PWM) over 5 seconds
  for (int pwmValue = 0; pwmValue <= 255; pwmValue++) {
    analogWrite(controlPin, pwmValue); // Send PWM signal to control the output
    delay(20); // Wait for a short time before increasing the value
  }

  // Gradually decrease the brightness (PWM) over 5 seconds
  for (int pwmValue = 255; pwmValue >= 0; pwmValue--) {
    analogWrite(controlPin, pwmValue); // Send PWM signal to control the output
    delay(20); // Wait for a short time before decreasing the value
  }
}
