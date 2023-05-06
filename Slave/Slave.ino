#include <Salva_Slave.h>

/*
* Sketch For Slave Arduino
* - Voltage Sensor Connected To Pin 12
* - Servo 1 Connected To Pin 6
* - Servo 2 Connected To Pin 5
* - Stepper Motor Driver: PUL: Pin 3 / DIR: Pin 2
* Started On: 18/03/2023
* Last Update: 6/05/2023
*/

SwitchesReceiver Salva_Switches;
VoltSensor Salva_VoltSensor;

void setup() {
  Wire.begin(Salva_u8AtMegaSlaveAddress);
  Serial.begin(115200);
  stepperMotor_voidInit();
  Salva_VoltSensor.voltSensor_voidInit();
  Salva_Servo1.attach(servoMotor_u8Servo1Pin);
  Salva_Servo2.attach(servoMotor_u8Servo2Pin);
  Wire.onReceive(I2C_voidReceiveEvent);
  Wire.onRequest(I2C_voidRequestEvent);
}

void loop() {
  Salva_Switches.switches_voidSwitchModeReceiver();
}

void I2C_voidReceiveEvent(int Copy_s32Placeholder) {
  u8 Local_u8ReceivedSwitchesState = Wire.read();
  Salva_Switches.switches_voidSwitchesStateSetter((switches_enuStates)Local_u8ReceivedSwitchesState);
  if (Local_u8ReceivedSwitchesState == switches_enuSwitch2IsPressed) {
    u8 Local_u8ReceivedState = Wire.read();
    switch (Local_u8ReceivedState) {
      case servoMotor_u8CommandStop:
        Salva_Servo1.servoMotor_u8State = servoMotor_u8CommandStop;
        break;
      case servoMotor_u8CommandBuild:
        Salva_Servo1.servoMotor_u8State = servoMotor_u8CommandBuild;
        u8 Local_u8High = Wire.read();
        u8 Local_u8Low = Wire.read();
        Salva_Servo1.servoMotor_u8Setpoint = (Local_u8High << 8) | Local_u8Low;
        Salva_Servo1.servoMotor_u8RespiratoryRate = Wire.read();
        u8 Local_u8Inhale = Wire.read();
        u8 Local_u8Exhale = Wire.read();
        Salva_Servo1.servoMotor_f32IERate = f32(Local_u8Inhale) / Local_u8Exhale;
        u8 Local_u8HoldSeconds = Wire.read();
        u8 Local_u8HoldDecimals = Wire.read();
        Salva_Servo1.servoMotor_f32Hold = Local_u8HoldSeconds + Local_u8HoldDecimals / 100.0;
        Salva_Servo1.servoMotor_u8DeltaTime = Wire.read();
        break;
      default:
        /* Do Nothing */
        break;
    }
  } else {
    /* Do Nothing */
  }
}

void I2C_voidRequestEvent(){
  Wire.write(Salva_VoltSensor.voltSensor_u8GetReading());
}
