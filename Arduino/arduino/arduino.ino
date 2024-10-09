#include "WiFiEsp.h"
#include <WiFiEsp.h>
#include <WiFiEspClient.h>
#include <WiFiEspServer.h>
#include <WiFiEspUdp.h>
#include "ThingSpeak.h"
int number = 2;
int read;
int i;
// Emulate Serial1 on pins 6/7 if not present

char ssid[] = "Fulbright_Student";
char pass[] = "fulbright2018";
unsigned long myChannelNumber = "insert-channel-number";
const char * myWriteAPIKey = "insert-write-api-key";
WiFiEspClient client;

void setup() {
  Serial.begin(115200);  // Initialize serial
  Serial3.begin(115200);    // initialize ESP module
  pinMode(number, INPUT);
  WiFi.init(&Serial3);
  ThingSpeak.begin(client); 
}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(500);     
    } 
  }
  read = digitalRead(number);
  int x = ThingSpeak.writeField(myChannelNumber, 1, read, myWriteAPIKey);
  if(x == 200){
    Serial.print("Channel update successful. Data sent: "); Serial.println(read);
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  for (i = 0; i < 20; i++){
    Serial.print(" IR Sensor value: "); Serial.println(digitalRead(number));
    delay(1000);
  }
}