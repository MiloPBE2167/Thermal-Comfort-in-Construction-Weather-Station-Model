// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // convert the analog reading (which goes from 0 -1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (5.0 / 1023.0);
  float uv = voltage *10;
  float uvIntensity = map (voltage, 0, 3.3, 0, 15);
  // print out the value you read:
  Serial.print("Voltage = ");
  Serial.print(voltage);
  Serial.print("   |   ");
  Serial.print("UV index = ");
  Serial.println(uvIntensity);
  delay(500);
}
