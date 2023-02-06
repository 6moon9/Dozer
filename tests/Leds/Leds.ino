#include <Led.h>

LedRGB led1(26, 27, 28);
LedRGB led2(29, 30, 31);

void setup() {
  led1.on(0, 0, 255);
  led2.on();
}

void loop() {
  // put your main code here, to run repeatedly:

}
