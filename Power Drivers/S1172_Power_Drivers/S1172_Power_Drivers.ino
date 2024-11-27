const int controlPin = 9;  // PWM pin connected to the IN pin of S1172
const int loadPin = 3;     // Pin connected to the load (LED or motor)

void setup() {
  pinMode(controlPin, OUTPUT); // Set the control pin as an output
  pinMode(loadPin, OUTPUT);    // Set the load pin as an output (in case we are using an LED)
  Serial.begin(9600);          // Initialize serial communication for debugging
}

void loop() {
  // Gradually increase the brightness of the LED or speed of the motor using PWM
  for (int pwmValue = 0; pwmValue <= 255; pwmValue++) {
    analogWrite(controlPin, pwmValue); // Send PWM signal to the S1172 to control the load
    analogWrite(loadPin, pwmValue);    // Optionally control the load directly if needed
    Serial.print("PWM Value: ");
    Serial.println(pwmValue);
    delay(20); // Small delay for smooth transition
  }

  // Gradually decrease the brightness or speed
  for (int pwmValue = 255; pwmValue >= 0; pwmValue--) {
    analogWrite(controlPin, pwmValue); // Send PWM signal to the S1172 to control the load
    analogWrite(loadPin, pwmValue);    // Optionally control the load directly if needed
    Serial.print("PWM Value: ");
    Serial.println(pwmValue);
    delay(20); // Small delay for smooth transition
  }
}
