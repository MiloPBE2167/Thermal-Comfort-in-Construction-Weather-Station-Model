#define led_pin1 8
#define led_pin2 5

void setup() {
  pinMode(led_pin1, OUTPUT);
  pinMode(led_pin2, OUTPUT);
}

void loop() {
  digitalWrite(led_pin1,HIGH); // turn the led_1 on
  digitalWrite(led_pin2,LOW); // turn the led_2 off
  delay(200); // wait a second
  digitalWrite(led_pin1,LOW); // turn the led_1 off
  digitalWrite(led_pin2,HIGH); // turn the led_2 on
  delay(200); // wait a second
}
