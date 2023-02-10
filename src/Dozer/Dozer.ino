#include <Bluetooth.h>
#include <Mecanum.h>
#include <Report.h>
#include <BlackLineSensor.h>
#include <Led.h>
#include <Cherry.h>
#include <Timeout.h>

#define loopTime 20
#define debugMode false

//                          left                                   right                              mapping
//                   top            bottom                 top             bottom                  from      to
Mecanum mecanum(34, 35, 4, 1,   38, 39, 2, 1,   25,     37, 36, 3, 1,   32, 33, 5, 1,    7,      0, 1023,  0, 150);
//            in1,in2,pwm,offs in1,in2,pwm,offs,stby  in1,in2,pwm,offs in1,in2,pwm,offs,stby     min,max   min,max

#include <ExtraMeca.h>
Mecaside left(Left);
Mecaside right(Right);

Bluetooth bluetooth(&Serial1);
Report report(&Serial, debugMode, 100);

BlackLineSensor blackLine(A0, A1, A2);

LedRGB bluetoothLed(28, 27, 26);
LedRGB led2(31, 30, 29);

Barrier barrier(13);
ToCake toCake(11, 12);
ToBasket toBasket(10);
Costume costume(9);
Grabber grabber(7, 8, 650, 2600);

#include "AutoPilot.h"

void setup ()
{
  // Serial setup //
  {
    Serial1.begin(9600);
#if debugMode
    Serial.begin(9600);
    Serial.println("Serial communication's on...");
    Serial.println("Bluetooth communication's on...");
    Serial.println("Debug mode's on...");
#endif
  }
  // Setup and stop the robot  //
  {
    barrier.setup();
    toCake.setup();
    toBasket.setup();
    costume.setup();
    grabber.setup();
    bluetoothLed.off();
    stop();
    // autoPilot.drift(); // To drift // Only for fun // Do not use in tournament
  }
}

void loop ()
{
  report.print();
  if (bluetooth.receive())
  {
    if (bluetooth.lastError == DeserializationError::Ok)
    {
      report.ok++;
      report.prob = 0;
      bluetoothLed.on(0, 0, 255);
      // Switch //
      {
#if debugMode
        Serial.print("switch: "); Serial.println(bluetooth.json["switch"].as<bool>()); Serial.println();
#endif
        barrier.move(bluetooth.json["switch"].as<bool>());
      }
      // Keypad //
      {
#if debugMode
        Serial.print("key: "); Serial.println(bluetooth.json["keypad"].as<int>()); Serial.println();
#endif
        switch (bluetooth.json["keypad"].as<int>())
        {
          case 1:
            grabber.grab();
            break;
          case 2:
            toBasket.toggle();
            break;
          case 3:
            toCake.open();
            break;
          case 4:
            autoPilot.line.find.left();
            break;
          case 5:
            autoPilot.line.follow.forward();
            break;
          case 6:
            autoPilot.line.find.right();
            break;
          case 10:
            costume.deploy();
            break;
          case 11:
            stop();
            break;
          case 12:
            autoPilot.winDance();
            break;
        }
      }
      // Motors //
      {
#if debugMode
        Serial.print("y.l: "); Serial.println(bluetooth.json["joysticks"]["left"]["y"].as<int>());
        Serial.print("y.r: "); Serial.println(bluetooth.json["joysticks"]["right"]["y"].as<int>()); Serial.println();
        Serial.print("x.l: "); Serial.println(bluetooth.json["joysticks"]["left"]["x"].as<int>());
        Serial.print("x.r: "); Serial.println(bluetooth.json["joysticks"]["right"]["x"].as<int>()); Serial.println(); Serial.println();
#endif
        // Y
        {
          left.move(bluetooth.json["joysticks"]["left"]["y"].as<int>());
          right.move(bluetooth.json["joysticks"]["right"]["y"].as<int>());
        }
        // X
        {
          mecanum.sideway(bluetooth.json["joysticks"]["left"]["x"].as<int>());
          mecanum.diagonal(bluetooth.json["joysticks"]["right"]["x"].as<int>(), bluetooth.json["joysticks"]["left"]["y"].as<int>());
        }
      }
      /*  // Response //
        {
        bluetooth.json.clear();
        bluetooth.json["blackLine"]["pattern"] = blackLine.getPattern();
        bluetooth.json["blackLine"]["onTheLine"] = blackLine.lastPattern == Position.Pattern.OnTheLine;
        bluetooth.send();
        }*/
    }
    else
    {
      report.inv++;
      report.prob++;
      bluetooth.empty();
      bluetoothLed.on(255, 0, 0);
    }
  }
  else
  {
    report.ntr++;
    report.prob++;
    bluetooth.empty();
    bluetoothLed.off();
  }
  if (report.prob >= 10)
  {
    stop();
  }
  delay(loopTime);
}

void stop ()
{
#if debugMode
  Serial.println("stop"); Serial.println();
#endif
  mecanum.stop();
  // Add others actuators
}
