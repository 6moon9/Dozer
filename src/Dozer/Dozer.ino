#include <Bluetooth.h>
#include <Mecanum.h>
#include <Report.h>

#define loopTime 100

Bluetooth bluetooth(&Serial1);

Mecanum mecanum;

struct
{
    void forward (int speed)
    {
        mecanum.motors[Left][Top].backward(speed);
        mecanum.motors[Left][Bottom].forward(speed);
        mecanum.motors[Right][Top].backward(speed);
        mecanum.motors[Right][Bottom].forward(speed);
    }
    void backward (int speed)
    {
        mecanum.motors[Left][Top].forward(speed);
        mecanum.motors[Left][Bottom].backward(speed);
        mecanum.motors[Right][Top].forward(speed);
        mecanum.motors[Right][Bottom].backward(speed);
    }
} sideway;
struct
{
    void forward (int speed)
    {
        mecanum.motors[Left][Top].forward(speed);
        mecanum.motors[Left][Bottom].stop();
        mecanum.motors[Right][Top].stop();
        mecanum.motors[Right][Bottom].forward(speed);    
    }
    void backward (int speed)
    {
        mecanum.motors[Left][Top].stop();
        mecanum.motors[Left][Bottom].forward(speed);
        mecanum.motors[Right][Top].forward(speed);
        mecanum.motors[Right][Bottom].stop();
    }
} diagonal;

struct Mecaside
{
    public:
        Mecaside(int iSide)
        {
            side = iSide;
        }
        int side = 0;
        void forward(int speed)
        {
            mecanum.motors[side][0].forward(speed);
            mecanum.motors[side][1].forward(speed);
        }
        void backward(int speed)
        {
            mecanum.motors[side][0].backward(speed);
            mecanum.motors[side][1].backward(speed);
        }
        void stop()
        {
            mecanum.motors[side][0].stop();
            mecanum.motors[side][1].stop();
        }
};

Mecaside left(Left);
Mecaside right(Right);
Report report(&Serial, true, 5 * (1000 / loopTime));

void setup ()
{
  // Serial setup //
  {
    Serial1.begin(9600);
    Serial.begin(9600);
    Serial.println("Computer serial communication's on...");
  }
  // Mecanum setup //
  {
    mecanum.stop();
  }
}

void loop ()
{
  if (bluetooth.receive())
  {
    if (bluetooth.lastError == DeserializationError::Ok)
    {
      report.ok++;
      serializeJson(bluetooth.json, Serial);
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
              sideway.forward(1023);
              break;
            case -3:
              sideway.backward(1023);
              break;
            case -1:
              mecanum.stop();
              break;
            default:
              if (value > 512) 
                sideway.forward(value);
              else if (value < 512)
                sideway.backward(value);
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
              mecanum.stop();
              break;
            default:
              if (value > 512) 
                diagonal.forward(value);
              else if (value < 512)
                diagonal.backward(value);
          }
        }
      }
    }
    else
    {
      report.inv++;
      bluetooth.empty();
    }
  }
  else
  {
    report.ntr++;
  }
  report.print();
  delay(loopTime);
}
