#include <Mecanum.h>

//                          left                                   right
//                  top              bottom                top              bottom
Mecanum mecanum(22, 23, 2, 1,   24, 25, 3, 1, 6,       26, 27, 4, 1,   28, 29, 5, 1, 7,        0, 1023);
//            in1,in2,pwm,offs in1,in2,pwm,offs,stby  in1,in2,pwm,offs in1,in2,pwm,offs,stby  min  max

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("forward");
  mecanum.forward(1023);
  delay(1000);
  Serial.println("stop");
  mecanum.stop();
  delay(1000);
  Serial.println("backward");
  mecanum.backward(1023);
  delay(1000);
  Serial.println("stop");
  mecanum.stop();
  delay(1000);
}
