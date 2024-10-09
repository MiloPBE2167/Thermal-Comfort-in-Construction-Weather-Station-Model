/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>
#include <Wire.h>              
#include <LiquidCrystal_I2C.h> 
#include <Arduino.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 8 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
// #include <DHT.h>
// #include <DHT_U.h>
// #define DHTPIN 8
// #define DHTTYPE DHT22
// DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4); // 0x27 is I2C module address 

//_________
int measurePin = A0; //Connect dust sensor to Arduino A0 pin
int ledPower = 7;   //Connect 3 led driver pins of dust sensor to Arduino D2
int samplingTime = 280; // time required to sample signal coming out  of the sensor
int deltaTime = 40; // 
int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
//_________


//_________
const int hallSensorPin = 2; //( chân tín hiệu : ONLY pin 2) 
const float mmPerTilt = 0.00195; // Amount of rainfall (in mm) per sensor tilt
//_________


//_________
unsigned long startTime = 0;
volatile unsigned long tipCount = 0;
volatile bool raining = false;
float rainfallAmount;
float rainfallSpeed;
//_________

//_________
//pin definitions
int UV_OUT = A1;    //Sensor Output
int REF_3V3 = A2;   //3.3V power on the Arduino board
//_________


float t;


//Takes an average of readings on a given pin
//Returns the average
int analogRead_average(int pinToRead)
{
  int NumberOfSamples = 8;
  int runningValue = 0; 

  for(int x = 0; x < NumberOfSamples; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= NumberOfSamples;

  return(runningValue);
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

File myFile;
const int chipSelect = 53;
String fileName = "datalog1.txt";

void setup() {
  lcd.init();            
  lcd.begin(20,4);      
  lcd.backlight();

  Serial.begin(9600);

  pinMode(hallSensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hallSensorPin), tipCount, RISING);
  
  sensors.begin(); 
  // dht.begin();
  
  pinMode(ledPower,OUTPUT);
  
  sdSetting();
  delay(1000);
  }

void loop() {

//_________
  sensors.requestTemperatures();
  t = sensors.getTempCByIndex(0);
  // float Humidity = dht.readHumidity();
  // // Read temperature as Celsius (the default)
  // float Temperature = dht.readTemperature();
  // // Read temperature as Fahrenheit (isFahrenheit = true)
  // float Temp_Fahrenheit = dht.readTemperature(true);
  // //Check if any reads failed and exit early (to try again).
  // if (isnan(Humidity) || isnan(Temperature) || isnan(Temp_Fahrenheit)) {
  //   lcd.setCursor(0,3);
  //   lcd.print("Failed to read!");
  //   return;
  // }
//_________


//_________
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin); // read the dust value
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity = 170 * calcVoltage - 0.1;
//_________


//_________
  // int sensorValue = analogRead(A3);
  // float outvoltage = sensorValue * (5.0 / 1023.0);
  // float Level = 6 * outvoltage; //The level of wind speed is proportional to the output voltage.
//_________


//_________
  unsigned long currentTime = millis();
  unsigned long deltaTime = currentTime - startTime;

  if (deltaTime >= 10000) { // Check for 10 seconds
    detachInterrupt(digitalPinToInterrupt(hallSensorPin)); // Disable interrupt during calculations
    rainfallAmount = tipCount * mmPerTilt;
    rainfallSpeed = rainfallAmount / (deltaTime / 3600000.0); // Convert deltaTime to hours
    

    // Reset variables for the next 10 seconds
    startTime = currentTime;
    tipCount = 0;
    raining = false;
    attachInterrupt(digitalPinToInterrupt(hallSensorPin), tipCounter, RISING);
  }
//_________


//_________
  int uv_Level = analogRead_average(UV_OUT);
  int ref_Level = analogRead_average(REF_3V3);

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float output_Voltage = 3.3 / ref_Level * uv_Level;

  float uvIntensity = mapfloat(output_Voltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level -numbers from datasheet-
//_________


//_________
  // lcd.setCursor(0,0);
  // lcd.print("Humidity:");
  // lcd.print(Humidity);
  // lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.print(sensors.getTempCByIndex(0));
  lcd.print(" do C");

  lcd.setCursor(0,2);
  lcd.print("Dust: ");
  lcd.print(dustDensity); 
  lcd.print("ug/m3");

  // lcd.setCursor(0,3);
  // lcd.print("Wind speed: ");
  // lcd.print(Level);
  // lcd.print("m/s");

  delay(2000);
  lcd.clear();  
//_________


//_________
  lcd.setCursor(0,1);
  lcd.print("Rain Speed:");
  lcd.print(rainfallSpeed);
  lcd.print("mm/h");

  lcd.setCursor(0,2);
  lcd.print("UV: ");
  lcd.print(uvIntensity);
  lcd.print("mW/cm2");

  delay(2000); // one seconds
  lcd.clear();
//_________


  String temp = printTEMP(sensors.getTempCByIndex(0));
  String dust = printDUST(dustDensity);
  // String wind = printWIND(Level);
  String rain = printRAIN(rainfallSpeed);
  String uv = printUV(uvIntensity);
  writeToSD(fileName,temp+" "+dust+" "+rain+" "+uv);
  delay(1000);

}


void sdSetting() {
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file for reading:
  myFile = SD.open(fileName);
  if (myFile) {
    Serial.println(fileName);

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening");
  }

  // delete the file:
//  Serial.println("Removing...");
//  SD.remove(fileName);

//  writeToSD(fileName, "Start write data to file");

}


void writeToSD(String fileName, String str) {
  File dataFile = SD.open(fileName, FILE_WRITE);
  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(str);
    dataFile.close();
    // print to the serial port too:
    Serial.print("Saved: ");
    Serial.println(str);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening file");
  }
}


String printTEMP(float t) {
  Serial.print("\tTemperature: ");
  Serial.print(t);
  return String(t);
}


String printDUST(float dustDensity) {
  Serial.print("\tDust: ");
  Serial.print(dustDensity);
  return String(dustDensity);
}


// String printWIND(float Level) {
//   Serial.print("\tWind: ");
//   Serial.print(Level);
//   return String(Level);
// }


String printRAIN(float rainfallSpeed) {
  Serial.print("\tRain: ");
  Serial.print(rainfallSpeed);
  return String(rainfallSpeed);
}


String printUV(float uvIntensity) {
  Serial.print("\tUV: ");
  Serial.println(uvIntensity);
  return String(uvIntensity);
}


void tipCounter() {
  tipCount++;
  raining = true;
}
