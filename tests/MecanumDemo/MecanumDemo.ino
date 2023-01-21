#include <Mecanum.h>

//                          left                                   right                              mapping
//                   top            bottom                 top             bottom                  from      to
Mecanum mecanum(34, 35, 4, 1,   38, 39, 2, 1,   25,     37, 36, 3, 1,   32, 33, 5, 1,    7,      0, 1023,  0, 180);
//            in1,in2,pwm,offs in1,in2,pwm,offs,stby  in1,in2,pwm,offs in1,in2,pwm,offs,stby     min,max   min,max

#include <ExtraMeca.h>
Mecaside left(Left);
Mecaside right(Right);

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
  
  Serial.println("sideway left");
  mecanum.sideway(1023);
  delay(1000);
  
  Serial.println("stop");
  mecanum.stop();
  delay(1000);
  
  Serial.println("sideway right");
  mecanum.sideway(-1023);
  delay(1000);
  
  Serial.println("left");
  left.move(1023);
  delay(1000);
  
  Serial.println("stop");
  mecanum.stop();
  delay(1000);
  
  Serial.println("right");
  right.move(1023);
  delay(1000);
  
  Serial.println("diagonal left forward");
  mecanum.diagonal(1023, 1023);
  delay(1000);
  
  Serial.println("diagonal right forward");
  mecanum.diagonal(-1023, 1023);
  delay(1000);
  
  Serial.println("diagonal left backward");
  mecanum.diagonal(1023, -1023);
  delay(1000);
  
  Serial.println("diagonal right backward");
  mecanum.diagonal(-1023, -1023);
  delay(1000);
  
  Serial.println("stop");
  mecanum.stop();
  delay(1000);
}
