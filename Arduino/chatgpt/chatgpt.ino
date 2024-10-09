// Define the analog input pin for UV sensor
const int uvSensorPin = A0;

void setup() {
  // Initialize Serial communication (optional, for debugging purposes)
  Serial.begin(9600);
}

void loop() {
  // Read analog value from UV sensor
  int uvSensorValue = analogRead(uvSensorPin);

  // Map the analog value to UV intensity value (if necessary)
  // You might need to consult the sensor datasheet to calibrate this mapping.
  float uvIntensity = mapToUVIntensity(uvSensorValue);

  // Print UV intensity to Serial Monitor (optional)
  Serial.print("UV Intensity: ");
  Serial.println(uvIntensity);

  // Add a delay to prevent rapid readings (adjust this as needed)
  delay(1000);
}

// Helper function to map the analog value to UV intensity (if necessary)
float mapToUVIntensity(int value) {
  // You may need to calibrate this mapping based on the sensor datasheet.
  // This function should be adapted to the sensor's actual specifications.
  float uvIntensity = map(value, 0, 1023, 0, 15.0);
  return uvIntensity;
}
