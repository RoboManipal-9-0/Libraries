/*
  ThreeWheelMotorBase.cpp - Library code for controlling a three wheel bot
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

#include "ThreeWheelMotorBase.h"

// ################### Setup Functions ######################
// Attah the Magnitude pins, Direction pins and Voltage levels required to impart CCW angular momentum to the bot
void ThreeWheelMotorBase::attachMagDirPins(int mags[3], int dirs[3], boolean ccw_dirs[3]) {
  // Basic initialization
  for (int i = 0; i < 3; i++) {
    // PWM pins
    this->MOTOR_PWM_PINS[i] = mags[i];
    pinMode(MOTOR_PWM_PINS[i], OUTPUT);
    // DIR - Direction pins
    this->MOTOR_DIR_PINS[i] = dirs[i];
    pinMode(MOTOR_DIR_PINS[i], OUTPUT);
    // Voltage level pins
    this->CCW_MOTION_VOLTAGE_LEVEL[i] = ccw_dirs[i];
    // 0V to both the pins (precautionary)
    digitalWrite(MOTOR_DIR_PINS[i],LOW);
    analogWrite(MOTOR_PWM_PINS[i], 0);
  }
}
// Set the threshold limit for the magnitude of every wheel
void ThreeWheelMotorBase::setThreshold(int MaxMags[3]) {
  for (int i = 0; i < 3; i++) {
    this->MAX_PWM_THRESHOLD[i] = MaxMags[i];
  }
}
void ThreeWheelMotorBase::setThreshold(int MaxMag) {
  int mags[3] = {MaxMag, MaxMag, MaxMag};
  this->setThreshold(mags);
}

// ################### Actuation Functions ######################
// #private : Set the motor at motorNumber to magnitude Magnitude (if +ve then it imparts CCW angular momentum, if -ve then it imparts CW angular momentum)
void ThreeWheelMotorBase::setMotorPWM(int motorNumber, float Magnitude) {
  // Write the direction level
  if (Magnitude > 0) {
    digitalWrite(MOTOR_DIR_PINS[motorNumber], CCW_MOTION_VOLTAGE_LEVEL[motorNumber]);
  } else {
    digitalWrite(MOTOR_DIR_PINS[motorNumber], !(CCW_MOTION_VOLTAGE_LEVEL[motorNumber]));
  }
  // Write the voltage level (absolute value)
  analogWrite(MOTOR_PWM_PINS[motorNumber], abs(Magnitude));
}
void ThreeWheelMotorBase::moveAtMagInDirWithOmega(float vel, float angle, float w) {
  // The main motion code : DO NOT EDIT IF YOU AREN'T CLEAR WHAT YOUR CHANGES WILL DO
  /*
    * The Main DCM is
    [
      1 1 1
      1 -cosd(60) -cosd(60)
      0 -sind(60) -sind(60)
    ]
    *
    [V1;V2;V3]
    =
    [w;vel*sin(angle);vel*cos(angle)]
    This gives the equations of
    [v1;v2;v3] = [
      1/3, 2/3, 0
      1/3, -1/3, -0.577350269
      1/3, -1/3, 0.577350269
    ]
    *
    [w;vel*sin(angle);vel*cos(angle)]
    Now, just solve
    V1 = (1/3) * w + (2/3) * (V*sin(angle));
    V2 = (1/3) * w - (1/3) * (V*sin(angle)) - 0.577350269 * (V*cos(angle));
    V3 = (1/3) * w - (1/3) * (V*sin(angle)) + 0.577350269 * (V*cos(angle));
    (Change indexes, because it's in order 0,1,2)
  */
  float mag0 = (1.0/3.0) * w + (2.0/3.0) * (vel * sin(angle));
  float mag1 = (1.0/3.0) * w - (1.0/3.0) * (vel * sin(angle)) - 0.577350269 * (vel * cos(angle));
  float mag2 = (1.0/3.0) * w - (1.0/3.0) * (vel * sin(angle)) + 0.577350269 * (vel * cos(angle));
  this->setMotorPWM(0, mag0);
  this->setMotorPWM(1, mag1);
  this->setMotorPWM(2, mag2);
}
// Move at magnitude (Magnitude) in direction (Angle - in Radians). Angle is measured CCW w.r.t +Y axis
void ThreeWheelMotorBase::moveAtMagInDir_AngleRAD(float Magnitude, float Angle) {
  this->moveAtMagInDirWithOmega(Magnitude,Angle,0);
}
// Move at magnitude (Magnitude) in direction (Angle - in Degrees). Angle is measured CCW w.r.t +Y axis
void ThreeWheelMotorBase::moveAtMagInDir_AngleDEG(float Magnitude, float Angle) {
  this->moveAtMagInDir_AngleRAD(Magnitude, Angle * (PI/180.0));
}
// Move at magnitude (Magnitude) in direction (Angle - in Degrees). Angle is measured CCW w.r.t +Y axis
void ThreeWheelMotorBase::moveAtMagInDir(float Magnitude, float Angle) {
  this->moveAtMagInDir_AngleDEG(Magnitude, Angle);
}
