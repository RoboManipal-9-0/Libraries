/*
  ThreeWheelMotorBase.h - Library for controlling a three wheel bot
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Check for the flags of the class being defined
#ifndef ThreeWheelMotorBase_h
#define ThreeWheelMotorBase_h

// Include basic Arduino functions
#include "Arduino.h"

// Class code here
class ThreeWheelMotorBase {
private:
  // Motor Direction and PWM pins, as observed in counter clockwise in delta formation sequence
  // Direction pins
  int MOTOR_DIR_PINS[3];
  boolean CCW_MOTION_VOLTAGE_LEVEL[3];  // The voltage level to give to the motor driver to make the bot move counter clockwise
  // PWM pins
  int MOTOR_PWM_PINS[3];
  int MAX_PWM_THRESHOLD[3];
  // Current Statistics
  int CURRENT_MAG[3]; // The current magnitude on motors
  boolean CURRENT_VOLTAGE_LEVEL[3]; // The current voltage level of motors

  // Debugger (In pipeline)

  // Motion of one wheel : Set the motor[i] to PWM
  void setMotorPWM(int i, float mag);
public:
  // Movement of wheels
  void attachMagDirPins(int Mag_pins[3], int Dir_pins[3], boolean CCWDirs[3]);  // Attach the magnitude and direction pins
  void moveAtMagInDir_AngleRAD(float Magnitude, float Angle);  // Move the bot at a particular magnitude at an angle (in radians)
  void moveAtMagInDir_AngleDEG(float Magnitude, float Angle);  // Move the bot at a particular magnitude at an angle (in degrees)
  void moveAtMagInDir(float Magnitude, float Angle);  // Move the bot at a particular magnitude at an angle (in degrees)
  void moveAtMagInDirWithOmega(float magnitude, float theta, float omega); // Move the bot at a particular magnitude at an angle (in degrees) with a rotation about center
  void setThreshold(float Magnitudes[3]); // Set the thresholds of the wheels
  void setThreshold(float Magnitude); // Set the threshold of the wheels (to the same value)
};

#endif
