/*


 Interfacing Sharp Optical Dust Sensor GP2Y1014AU0F with Arduino


*/


#define measurePin = 0; //Connect dust sensor to Arduino A0 pin


#define ledPower = 7;   //Connect 3 led driver pins of dust sensor to Arduino D2


int samplingTime = 280; // time required to sample signal coming out   of the sensor


int deltaTime = 40; // 


int sleepTime = 9680;


float voMeasured = 0;


float calcVoltage = 0;


float dustDensity = 0;


void setup(){


  Serial.begin(9600);


  pinMode(ledPower,OUTPUT);


}


void loop(){


  digitalWrite(ledPower,LOW); // power on the LED


  delayMicroseconds(samplingTime);


  voMeasured = analogRead(measurePin); // read the dust value


  delayMicroseconds(deltaTime);


  digitalWrite(ledPower,HIGH); // turn the LED off


  delayMicroseconds(sleepTime);


  // 0 - 5V mapped to 0 - 1023 integer values


  // recover voltage


  calcVoltage = voMeasured * (5.0 / 1024.0);


  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/


  // Chris Nafis (c) 2012


  dustDensity = 170 * calcVoltage - 0.1;


  Serial.println(dustDensity); // unit: ug/m3


  delay(1000);


}