/*
* Sketch For Slave Arduino
* - Voltage Sensor Connected To Pin 12
* - Servo 1 Connected To Pin 6
* - Servo 2 Connected To Pin 5
* - Stepper Motor Driver: PUL: Pin 3 / DIR: Pin 2
* Started On: 18/03/2023
* Last Update: 18/03/2023
*/

/* For Stepper Motor*/
#include <AccelStepper.h>
#include <MultiStepper.h>
/* For Servo Motor*/
#include <Servo.h>
#include <Wire.h>

#define voltSensor 12
#define servo1 6
#define servo2 5
#define Stepper_PUL 3
#define Stepper_DIR 2
#define delay_of_Stepper 700
#define Number_of_rotation_MODE1 120
#define Number_of_rotation_MODE2 30
#define switch1_isPressed 1
#define switch2_isPressed 2
#define AtMega_Address 0x08

void setup() {
  Wire.begin();
  pinMode(Stepper_PUL, OUTPUT);
  pinMode(Stepper_DIR, OUTPUT);
}

void loop() {
  Wire.requestFrom(AtMega_Address, 2);
  while (Wire.available()) {
    byte switchState = Wire.read();
    switch (switchState) {
      case switch1_isPressed:
        stepper(Number_of_rotation_MODE1);
        break;
      case switch2_isPressed:
        stepper(Number_of_rotation_MODE2);
        break;
    }
  }
}

void stepper(int Number_Of_rotations) {
  digitalWrite(Stepper_DIR, HIGH);
  for (int x = 0; x < 200 * Number_Of_rotations; x++) {
    digitalWrite(Stepper_PUL, HIGH);
    delayMicroseconds(delay_of_Stepper);
    digitalWrite(Stepper_PUL, LOW);
    delayMicroseconds(delay_of_Stepper);
  }
}