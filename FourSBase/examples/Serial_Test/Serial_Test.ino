/*
  Serial_Test.ino - Example to Test Four wheel holonomic drive base
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Shashank Goyal
  Last commit done by : Shashank Goyal
*/

/************************************************

  Format for Command -

  P100A30W0 -> 
  Translatory Velocity = 100
  Angle = 30
  Angular Velocity = 0

  M5 -> 
  Move at the set parameter values for 5 Seconds.

*************************************************/

#include <FourSBase.h>

int PWM_pins[] = {12, 10, 8, 6};    // List of PWM pins
int DIR_pins[] = {11, 9, 7, 5}; // List of DIR pins
bool reverseDIRs[] = {false, false, false, false};

float trans_vel = 0;
float angle = 0;
float ang_vel = 0;

FourSBase Base;

void setup()
{
  Serial.begin(9600);
  Base.debugger.Initialize("FourSBase", &Serial, DEBUG);
  Base.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
}

void loop()
{
  while (Serial.available())
  {
    switch (Serial.read()) {
      case 'P':
        trans_vel = Serial.parseInt();
        break;
      case 'A':
        angle = Serial.parseInt();
        break;
      case 'W':
        ang_vel = Serial.parseInt();
        break;
      case 'M':
        Base.Move(trans_vel, angle, ang_vel);
        delay(Serial.parseInt() * 1000);
        break;
      default:
        Base.Move(0, 0, 0);
    }
  }
}
