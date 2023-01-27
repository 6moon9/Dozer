#include <Bluetooth.h>
#include <Mecanum.h>
#include <Report.h>
#include <BlackLineSensor.h>
#include <Led.h>
#include <Servo.h>

#define loopTime 20
#define debugMode false // Pass to false for production

//                          left                                   right                              mapping
//                   top            bottom                 top             bottom                  from      to
Mecanum mecanum(34, 35, 4, 1,   38, 39, 2, 1,   25,     37, 36, 3, 1,   32, 33, 5, 1,    7,      0, 1023,  0, 180);
//            in1,in2,pwm,offs in1,in2,pwm,offs,stby  in1,in2,pwm,offs in1,in2,pwm,offs,stby     min,max   min,max

#include <ExtraMeca.h>
Mecaside left(Left);
Mecaside right(Right);

Bluetooth bluetooth(&Serial1);
Report report(&Serial, debugMode, 100);
BlackLineSensor blackLine(A0, A1, A2);
Led bluetoothLed(13);
Servo bariere;

#include "AutoPilot.h"
AutoPilot autoPilot;

bool oldSwitchValue = true;

void setup ()
{
  // Serial setup //
  {
    Serial1.begin(9600);
    Serial.begin(9600);
#if debugMode
    Serial.println("Serial communication's on...");
    Serial.println("Bluetooth communication's on...");
    Serial.println("Debug mode's on...");
#endif
  }
  // Stop the robot  //
  {
    bariere.attach(13);
    bariere.write(oldSwitchValue * 100);
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
      bluetoothLed.on();
      //serializeJsonPretty(bluetooth.json, Serial);
      // Switch //
      {
        if (bluetooth.json["switch"].as<bool>() != oldSwitchValue)
        {
          oldSwitchValue = bluetooth.json["switch"].as<bool>();
          Serial.println(oldSwitchValue);
          bariere.write(oldSwitchValue * 100);
        }
      }
      // Keypad //
      {
#if debugMode
        Serial.print("key: "); Serial.println(bluetooth.json["keypad"].as<int>()); Serial.println();
#endif
        switch (bluetooth.json["keypad"].as<int>())
        {
          case 1:
            break;
          case 2:
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
            autoPilot.drift();
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
      bluetoothLed.off();
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
