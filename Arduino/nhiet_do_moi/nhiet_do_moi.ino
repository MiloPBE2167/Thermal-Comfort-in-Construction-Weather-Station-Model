/*
 * Kết nối:
 *          VCC  ---- 5V (Arduino)
 *          GND  ---- GND (Arduino)
 *          DATA ----  2 (Arduino)
 */
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);
void setup(void) 
{ 
 Serial.begin(9600); 
 // Start up the library 
 sensors.begin(); 
} 
void loop(void) 
{ 
 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures();
 Serial.println("DONE"); 
 Serial.print("Temperature is: "); 
 Serial.print(sensors.getTempCByIndex(0));
 delay(1000); 
}