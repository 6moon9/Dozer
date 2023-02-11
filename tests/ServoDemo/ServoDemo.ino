#include <Cherry.h>

#define SERVO_1 13
#define SERVO_2 12
#define SERVO_3 11
#define SERVO_4 10
#define SERVO_5 9
#define SERVO_6 8
#define SERVO_7 7
#define SERVO_8 6

Barrier barrier(SERVO_1);
ToCake toCake(SERVO_2, SERVO_3, 90, 0, 90, 0);
ToBasket toBasket(SERVO_4);
Costume costume(SERVO_5);
Grabber grabber(SERVO_6, SERVO_7, 650, 2600, 400, 1000, 0, 130, 0, 130);

void setup() {
  Serial.begin(9600);
  grabber.setup();
  barrier.setup();
  toCake.setup();
  toBasket.setup();
  costume.setup();
  grabber.grab();
  toCake.open();
}

void loop() {
  Serial.println("Grabber: grab");
  grabber.grab();
  delay(2000);
  Serial.println("Costume: deploy");
  costume.deploy();
  delay(2000);
  Serial.println("Barrier: open");
  barrier.open();
  delay(2000);
  Serial.println("Barrier: close");
  barrier.close();
  delay(2000);
  Serial.println("ToCake: open");
  toCake.open();
  delay(2000);
  Serial.println("ToBasket: open");
  toBasket.open();
  delay(2000);
  Serial.println("ToBasket: close");
  toBasket.close();
  delay(2000);
}
