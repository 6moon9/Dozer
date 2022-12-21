# Dozer
This is the robot code from the Ingenium team.

## Software
### Description
The [src code](./src/) consists of an arduino sketch containing:
* [`Dozer.ino`](#dozerino)
* [`AutoPilot.h`](#autopiloth)
* [`ExtraMeca.h`](#extramecah)

#### [`Dozer.ino`](./src/Dozer/Dozer.ino)
##### Receive values
* Read values received by `Bluetooth` on the `Serial1` and deserialize them with the [ArduinoJson](https://github.com/bblanchon/ArduinoJson)

##### Robot control
* `switch...case` the value of the keypad and make actions:

| Number | Key    | Action | Description |
| :----: | :----: | ------ | ----------- |
| 1      | 1      |        |             |
| 2      | 2      |        |             |
| 3      | 3      |        |             |
| 4      | 4      |        |             |
| 5      | 5      |        |             |
| 6      | 6      |        |             |
| 7      | 7      |        |             |
| 8      | 8      |        |             |
| 9      | 9      |        |             |
| 10     | #      |        |             |
| 11     | 0      |        |             |
| 12     | *      |        |             |

* Control the motors according the values of the joysticks

#### [`AutoPilot.h`](./src/Dozer/AutoPilot.h)
Provides auto pilot functions such as:
* Follow the black line

#### [`ExtraMeca.h`](./src/Dozer/ExtraMeca.h)
Extends the use of the mecanum library by adding:
* sides (left and right)
* sideway movements
* diagonal movements

### Dependecies
The INO file depends of the following list of libraries:
* [Bluetooth](https://github.com/IngeniumTeam/Bluetooth)
    * [Arduino/SoftwareSerial](https://docs.arduino.cc/learn/built-in-libraries/software-serial): This library is built into the Arduino IDE
    * [bblanchon/ArduinoJson](https://github.com/bblanchon/ArduinoJson)
* [Mecanum](https://github.com/IngeniumTeam/Mecanum)
    * [Motor](https://github.com/IngeniumTeam/Motor)
* [BlackLineSensor](https://github.com/IngeniumTeam/BlackLineSensor)
* [HCSR04](https://github.com/IngeniumTeam/HCSR04)
* [Report](https://github.com/IngeniumTeam/Report)

## Hardware
* Arduino Mega 2560
* 4 motors equipped with [mecanum wheels](https://en.wikipedia.org/wiki/Mecanum_wheel)
* HC-05 bluetooth module
