// #include <DHT.h>
// #include <DHT_U.h>

// #define DHTPIN 2
// #define DHTTYPE DHT22
// DHT dht(DHTPIN, DHTTYPE);

  //int measurePin = A2; //Connect dust sensor to Arduino A2 pin
  //int ledPower = 7;   //Connect 3 led driver pins of dust sensor to Arduino D2
  //int samplingTime = 280; // time required to sample signal coming out  of the sensor
  //int deltaTime = 40;
  //int sleepTime = 9680;

  //float voMeasured = 0;
  //float calcVoltage = 0;
  //float dustDensity = 0;


void setup() {
  Serial.begin(9600);
  // dht.begin();
  //pinMode(ledPower,OUTPUT);
}

void loop() {
  int sensorValue = analogRead(A0); //Connect wind speed sensor to Arduino A0 pin
  int sensorValue_UV = analogRead(A1); //Connect UV sensor to Arduino A1 pin

  float outvoltage = sensorValue * (5.0 / 1023.0);
  float Level = 6 * outvoltage; //The level of wind speed is proportional to the output voltage.
  int voltage = sensorValue_UV * (5.0 / 1023.0);
  

  // float Humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  // float Temperature = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float Temp_Fahrenheit = dht.readTemperature(true);
  // Check if any reads failed and exit early (to try again).
  // if (isnan(Humidity) || isnan(Temperature) || isnan(Temp_Fahrenheit)) {
  //   Serial.println("Failed to read from DHT sensor!");
  //   return;
  // }

  
  Serial.print("Toc do gio ");
  Serial.print(Level);
  Serial.print("m/s");
  Serial.print("   |   ");
  Serial.print("UV index: ");
  Serial.print(voltage/.1);
  //Serial.println("   |   ");
  // Serial.print("Humidity: ");
  // Serial.print(Humidity);
  // Serial.print("%");
  // Serial.print("   |   ");
  // Serial.print("Temperature: ");
  // Serial.print(Temperature);
  // Serial.print("°C ");
  // Serial.print(Temp_Fahrenheit);
  // Serial.println("°F ");

  //digitalWrite(ledPower,LOW); // power on the LED
  //delayMicroseconds(samplingTime);
  //voMeasured = analogRead(measurePin); // read the dust value
  //delayMicroseconds(deltaTime);
  //digitalWrite(ledPower,HIGH); // turn the LED off
  //delayMicroseconds(sleepTime);
  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  //calcVoltage = voMeasured * (5.0 / 1024.0);
  //dustDensity = 170 * calcVoltage - 0.1;
  //Serial.print("dustDensity: ");
  //Serial.println(dustDensity); // unit: ug/m3


  //   Serial.println(" level now");
  Serial.println();
  delay(1000);
}