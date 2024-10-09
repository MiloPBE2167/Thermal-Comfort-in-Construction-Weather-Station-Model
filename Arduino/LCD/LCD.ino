#include <Wire.h>              
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x27, 20, 4); // 0x27 is I2C module address 
void setup()
{
lcd.init();            
lcd.begin(20,4);      
lcd.backlight();       
}


void loop()
{
lcd.setCursor(5, 0);       
lcd.print("Welcome to");  

lcd.setCursor(5, 1);      
lcd.print("saptaji.com");  

lcd.setCursor(2, 2);      
lcd.print(" "); 

delay(2000);
lcd.clear();   



lcd.setCursor(1, 0);
lcd.print("LCD 2004 Tutorial");

lcd.setCursor(5, 1);
lcd.print("using I2C module");

lcd.setCursor(0, 2);
lcd.print("and Arduino");

lcd.setCursor(8, 3);
lcd.print("Uno");

delay(2000);
lcd.clear();               
}