#include <BlackLineSensor.h>

BlackLineSensor blck(2, 3, 4);

void setup() {
  Serial.begin(9600);

}

void loop() {
  bool* values = blck.getValue();
  Serial.println(values[0]);
  Serial.println(values[1]);
  Serial.println(values[2]);
  Serial.println();
  delay(500);
}
