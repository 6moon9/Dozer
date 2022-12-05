#include <Bluetooth.h>
#include <Mecanum.h>
#include <Report.h>
#include <BlackLineSensor.h>
#include <HCSR04.h>

#define loopTime 100

//                   left             right
//                top    bottom   top    bottom
Mecanum mecanum(10, 11,   8, 9,   2, 3,   4, 5);

#include "ExtraMeca.h"
Mecaside left(Left);
Mecaside right(Right);
Sideway sideway;
Diagonal diagonal;
Bluetooth bluetooth(&Serial1);
//            Serial   debugMode   every 5 seconds
Report report(&Serial, true, 5 * (1000 / loopTime));
BlackLineSensor blackLine(A0, A1, A2);
//                echo trigger
HCSR04 backDistance(2, 3);

#include "AutoPilot.h"
AutoPilot autoPilot;

void setup ()
{
  // Serial setup //
  {
    Serial1.begin(9600);
    Serial.begin(9600);
    Serial.println("Serial communication's on...");
    Serial.println("Bluetooth communication's on...");
  }
  // Mecanum setup //
  {
    stop();
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
      //serializePrettyJson(bluetooth.json, Serial);
      /*// Keybull //
        {
        switch (bluetooth.json["keybull"].as<int>())
        {
          case 1:
            findTheLineToTheRight();
            goBackToCherry();
            break;
          case 2:
            break;
          case 3:
            findTheLineToTheLeft();
            goBackToCherry();
            break;

        }
        }*/
      // Motors //
      {
        int value;
        // Left Y //
        {
          value = bluetooth.json["joysticks"]["left"]["y"];
          switch (value) {
            case -2:
              left.forward(1023);
              break;
            case -3:
              left.backward(1023);
              break;
            case -1:
              left.stop();
              break;
            default:
              if (value > 512)
                left.forward(value);
              else if (value < 512)
                left.backward(value);
          }
        }
        // Right Y //
        {
          value = bluetooth.json["joysticks"]["right"]["y"];
          switch (value) {
            case -2:
              right.forward(1023);
              break;
            case -3:
              right.backward(1023);
              break;
            case -1:
              right.stop();
              break;
            default:
              if (value > 512)
                right.forward(value);
              else if (value < 512)
                right.backward(value);
          }
        }
        // Left X //
        {
          value = bluetooth.json["joysticks"]["left"]["x"];
          switch (value) {
            case -2:
              sideway.left(1023);
              break;
            case -3:
              sideway.right(1023);
              break;
            case -1:
              break;
            default:
              if (value > 512)
                sideway.left(value);
              else if (value < 512)
                sideway.right(value);
          }
        }
        // Right X //
        {
          value = bluetooth.json["joysticks"]["right"]["x"];
          switch (value) {
            case -2:
              diagonal.forward(1023);
              break;
            case -3:
              diagonal.backward(1023);
              break;
            case -1:
              break;
            default:
              if (value > 512)
                diagonal.forward(value);
              else if (value < 512)
                diagonal.backward(value);
          }
        }
      }
      /*// Response //
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
    }
  }
  else
  {
    report.ntr++;
    report.prob++;
  }
  if (report.prob >= 10)
  {
    stop();
  }
  delay(loopTime);
}

void stop ()
{
  mecanum.stop();
  // Add others actuators
}
