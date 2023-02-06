#include <Cherry.h>

Grabber grabber(5, 6, 650, 2600);
Barrier barrier(13);
ToCake toCake(11, 12);
ToBasket toBasket(10);
Costume costume(13);

void setup() {
  grabber.setup();
  barrier.setup();
  toCake.setup();
  toBasket.setup();
  costume.setup();
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
