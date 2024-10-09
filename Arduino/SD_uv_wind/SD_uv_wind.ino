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


//pin definitions
int UV_OUT = A0;    //Sensor Output
int REF_3V3 = A2;   //3.3V power on the Arduino board

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
  Serial.begin(9600);
  sdSetting();
  delay(1000);
  }


void loop() {

  //_________//
  int uv_Level = analogRead_average(UV_OUT);
  int ref_Level = analogRead_average(REF_3V3);

  //Use the 3.3V power pin as a reference to get a very accurate output value from sensor
  float output_Voltage = 3.3 / ref_Level * uv_Level;

  float uvIntensity = mapfloat(output_Voltage, 0.99, 2.8, 0.0, 15.0); //Convert the voltage to a UV intensity level -numbers from datasheet-
  //_________//

  //_________//
  int sensorValue = analogRead(A3);
  float outvoltage = sensorValue * (5.0 / 1023.0);
  float Level = 6 * outvoltage;
  //_________//

  String WS = printWS(uvIntensity, Level);
  writeToSD(fileName,WS);
  
  delay(1000); // one seconds
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


String printWS(float uvIntensity, float Level) {
  Serial.print("uv: ");
  Serial.print(uvIntensity);
  Serial.print("mW/cm2");
  Serial.print("\wind: ");
  Serial.print(Level);
  Serial.println("m/s");
  return String(uvIntensity) +" "+ String(Level);
}
