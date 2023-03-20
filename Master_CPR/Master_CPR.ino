/*
* Sketch For Master Arduino
* - Switch 1 (Used For Continous Mode) Connected To Pin 11
* - Switch 2 (Used For 30:2 Mode) Connected To Pin 9
* - Encoder Pins (Used For Variable Input Like RR and TV):
* SW: Pin 4 / DT: Pin 3 / CLK: Pin 2
* - LCD 20x4 Connected To I2C Lines
* - MAX30102 Connected To I2C Lines
* Started On: 18/03/2023
* Last Update: 18/03/2023
*/

/* For Rotary Encoder*/
#include <RotaryEncoder.h>
/* For LCD*/
#include <LiquidCrystal_I2C.h>
/* For Max 30102 Sensor*/
#include <MAX30105.h>
#include <heartRate.h>
#include <spo2_algorithm.h>
#include <Wire.h>

#define sw1 11
#define sw2 9
#define Encoder_sw 4
#define Encoder_dt 3
#define Encoder_clk 2
#define LCD_Address 0x00
#define MaxSensor_Address 0x00
#define AtMega_Address 0x08

void setup() {
  Wire.begin();
}

void loop() {
  bool switch1_State = digitalRead(sw1);
  bool switch2_State = digitalRead(sw2);
  Wire.beginTransmission(AtMega_Address);
  if (switch1_State) {
    Wire.write(1);
  } else if (switch2_State) {
    Wire.write(2);
  }
  Wire.endTransmission();
}