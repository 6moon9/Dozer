#include <Servo.h>

Servo servo;

int testPin = 9;

void setup() {
  Serial.begin(9600);
  servo.attach(testPin);
  servo.write(90);
}

void loop() {
  /*Serial.println("0");
  delay(2000);
  servo.write(100);
  Serial.println("180");
  delay(2000);*/
}
