// Arduino IR Sensor Code
int IRSensor = 9; // connect ir sensor module to Arduino pin 9

int LED = 13; // conect LED to Arduino pin 13

void setup()

{
  Serial.begin(9600); // Init Serila at 115200 Baud

  Serial.println("Serial Working"); // Test to check if serial is working or not

  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
}

void loop()

{
  int sensorStatus = digitalRead(IRSensor); // Set the GPIO as Input
  Serial.println(sensorStatus);
  if (sensorStatus == 0) // Check if the pin high or not

  {
    // if the pin is high turn off the onboard Led
    Serial.println("Canh_bao!");
  }

  else

  {
    //else turn on the onboard LED
    Serial.println("khum co gi");
  }
}