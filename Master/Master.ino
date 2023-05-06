#include <Salva_Master.h>

/*
* Sketch For Master Arduino
* - Switch 1 (Used For Continous Mode) Connected To Pin 11
* - Switch 2 (Used For 30:2 Mode) Connected To Pin 9
* - Encoder Pins (Used For Variable Input Like RR and TV):
* SW: Pin 4 / DT: Pin 3 / CLK: Pin 2
* - LCD 20x4 Connected To I2C Lines
* - MAX30102 Connected To I2C Lines
* Started On: 18/03/2023
* Last Update: 6/05/2023
*/

SwitchesTransmitter Salva_Switches;
SalvaHeartSensor Salva_HeartSensor;

void setup() {
  // Necessary Communications
  Wire.begin();
  Serial.begin(115200);
  // Initialize Switches
  Salva_Switches.switches_voidInit();
  // Initialize LCD
  Salva_LCD.liquidCrystal_voidInit();
  // Initialize Encoder
  Salva_Encoder.encoder_voidInit();
  // Initialize Heart Sensor
  Salva_HeartSensor.heartRateSensor_voidInit(Salva_HeartSensor);
  Salva_LCD.liquidCrystal_voidPositionUpdate(2, 1);
  Salva_LCD.print("Welcome To Salva");
  delay(1000);
  // Transmitting Push Button Data
  Salva_Switches.switches_voidSwitchModeTransmitter();
}

void loop() {
  Wire.requestFrom(Salva_u8AtMegaSlaveAddress, 1);
  Salva_LCD.liquidCrystal_voidPositionUpdate(16, 0);
  Salva_LCD.print(Wire.read());
  Salva_HeartSensor.heartRateSensor_voidBPMCalculator(Salva_HeartSensor);
}
