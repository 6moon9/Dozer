#include <Servo.h>

Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(7);
  servo.write(0);
  Serial.println("0");
  delay(2000);
  servo.write(180);
  Serial.println("180");
}

void loop() {
  // put your main code here, to run repeatedly:

}
