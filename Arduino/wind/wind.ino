void setup() {
  Serial.begin(9600);
}
void loop() {
  int sensorValue = analogRead(A0);
  float outvoltage = sensorValue * (5.0 / 1023.0);
  // Serial.print("Dien ap = ");
  // Serial.print(outvoltage);
  // Serial.println("V");
  float Level = 6 * outvoltage; //The level of wind speed is proportional to the output voltage.
  Serial.print("Toc do gio ");
  Serial.print(Level);
  //   Serial.println(" level now");
  Serial.println();
  delay(500);
}