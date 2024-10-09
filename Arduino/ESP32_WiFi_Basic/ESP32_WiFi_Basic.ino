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
// #define ERA_DEBUG

#define DEFAULT_MQTT_HOST "mqtt1.eoh.io"

// You should get Auth Token in the ERa App or ERa Dashboard
#define ERA_AUTH_TOKEN "5cce93b1-34cb-48cd-ac99-a8f8a80b2bd2"

#include <Arduino.h>
#include <ERa.hpp>
#include <ERa/ERaTimer.hpp>

const char ssid[] = "Quoc Khanh";
const char pass[] = "quockhanh2007";

int button = 32;
int led = 18;

ERaTimer timer;

void button_read() {
  int button_state = digitalRead(button);
  ERa.virtualWrite(button_state, V1);
}

ERA_WRITE(V2) {
  uint8_t led_state = param.getInt();
  digitalWrite(led, led_state);
}

/* This function print uptime every second */
void timerEvent() {
  button_read();
  ERA_LOG("Timer", "Uptime: %d", ERaMillis() / 1000L);
}

void setup() {
  /* Setup debug console */
  Serial.begin(115200);

  pinMode(button, INPUT);
  pinMode(led, OUTPUT);

  ERa.begin(ssid, pass);

  /* Setup timer called function every second */
  timer.setInterval(1000L, timerEvent);
}

void loop() {
  ERa.run();
  timer.run();
}