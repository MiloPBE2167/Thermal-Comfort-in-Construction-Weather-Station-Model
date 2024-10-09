#include <Wire.h>              
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 20, 4); // 0x27 is I2C module address
int const UV_SENSOR_PIN = A1; // UV sig

void setup() {

  lcd.init();            
  lcd.begin(20,4);      
  lcd.backlight(); 

  Serial.begin(9600);
}


void loop() {

  int sensorValue = analogRead(A0); // wind speed
  int sensorValue_UV = analogRead(UV_SENSOR_PIN); // UV

  float outvoltage = sensorValue * (5.0 / 1023.0);
  float Level = 6 * outvoltage; //The level of wind speed is proportional to the output voltage.

  float volts = sensorValue_UV * 5.0 / 1024.0;
  int UV_index = volts * 10; // UV index

// print wind speed in lcd
  lcd.setCursor(0, 0);
  lcd.print("Toc do gio: ");
  lcd.print(Level);
  lcd.print("m/s");

// print UV in lcd
  lcd.setCursor(0,1);
  lcd.print("UV index: ");
  lcd.print(UV_index);

// time delay
  delay(1000);
  lcd.clear();

}