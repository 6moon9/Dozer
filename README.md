# Dozer

This is the robot code from the Ingenium team.

The INO file depends of the following list of libraries:
- [Bluetooth](https://github.com/IngeniumTeam/Bluetooth)
- [Mecanum](https://github.com/IngeniumTeam/Mecanum)
- [BlackLineSensor](https://github.com/IngeniumTeam/BlackLineSensor)
- [HCSR04](https://github.com/IngeniumTeam/HCSR04)
- [Report](https://github.com/IngeniumTeam/Report)

There are two C Header file:
- [AutoPilot](./src/Dozer/AutoPilot.h): Provides auto pilot functions
- [ExtraMeca](./src/Dozer/ExtraMeca.h): extends the use of the mecanum library by adding sides (left and right) and sideway and diagonal movements

The hardware consists of an Arduino Mega 2560 board, four motors equipped with [mecanum wheels](https://en.wikipedia.org/wiki/Mecanum_wheel), A HCSR04 ultrasonic distance sensor.
Communication is ensured by an HC-05 bluetooth module. All messages are encoded in JSON.
