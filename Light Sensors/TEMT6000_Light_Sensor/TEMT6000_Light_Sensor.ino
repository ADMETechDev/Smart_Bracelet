int temt6000Pin = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(temt6000Pin);
  Serial.println(value); 
  delay(200);
}