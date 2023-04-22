#include <Timino.h>

void callback () {
  Serial.println("callback");
}

Interval interval(callback, 3000, false);

void setup() {
  Serial.begin(9600);
  interval.start();
}

void loop() {
  interval.loop();
}
