
/*************************************************************
  Download latest ERa library here:
    https://github.com/eoh-jsc/era-lib/releases/latest
    https://www.arduino.cc/reference/en/libraries/era
    https://registry.platformio.org/libraries/eoh-ltd/ERa/installation

    ERa website:                https://e-ra.io
    ERa blog:                   https://iotasia.org
    ERa forum:                  https://forum.eoh.io
    Follow us:                  https://www.fb.com/EoHPlatform
 *************************************************************/

// Enable debug console
// Set CORE_DEBUG_LEVEL = 3 first
#define ERA_DEBUG

#define DEFAULT_MQTT_HOST "mqtt1.eoh.io"

// You should get Auth Token in the ERa App or ERa Dashboard
#define ERA_AUTH_TOKEN "aa12d80e-b4bc-4aa6-9620-dccbad51c2ee"

#include <Arduino.h>
#include <ERa.hpp>
#include <ERa/ERaTimer.hpp>
#include<ESP8266WiFi.h>

const char* ssid = "Fulbright_Student1";
const char* password = "fulbright2018";

////////////////////////////////////////////////////

int LedPin = 13;


// ERaTimer timer; 
//ERA_WRITE(V0){
//int value = param.getInt();
//digitalWrite(13, value);
//ERa.virtualWrite(V0, digitalRead(13));
//Serial.println(value);
//}
//nhận dữ liệu pin A0 từ server


/* This function print uptime every second */
void timerEvent() {

    ERA_LOG("Timer", "Uptime: %d", ERaMillis() / 1000L);
}

void setup() {
    pinMode(LedPin, OUTPUT);
    digitalWrite(LedPin, LOW);

    /* Setup debug console */
    Serial.begin(115200);
    Serial.println();
    Serial.print("connecting to WiFi");
    Serial.print(ssid);

    WiFi.begin(ssid, password);

    Serial.println();
    Serial.print("Connecting");

    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println(".");
    }
    Serial.print("ModeMCU IP Address");
    Serial.print(WiFi.localIP());

    // ERa.begin(ssid, pass);

    // /* Setup timer called function every second */
    // timer.setInterval(1000L, timerEvent);
}

void loop() {
    // ERa.run();
    // timer.run();
    // Serial.read();

    digitalWrite(LedPin, HIGH);
    delay(500);
    digitalWrite(LedPin, LOW);
    delay(500);
}

