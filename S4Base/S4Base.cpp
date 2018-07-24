/*
  S4Base.h - Library for controlling a four wheel bot having an S type
             wheel configuration.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Including directives
#include "S4Base.h"

// ################## SETUP FUNCTIONS #######################
// Empty constructor
S4Base::S4Base() {
  // Do nothing
}
// Assignment constructor
S4Base::S4Base(int MOTOR_PINs[4], int DIR_PINs[4], bool REV_DIRs[4], int MAX_PWMs[4]) {
  // Assignment of motor pin connections
  this->AddMotorDriverPins(MOTOR_PWMs, DIR_PINs, REV_DIRs);
  // Assignment of Max magnitude
  this->AddMotorMAGLimit(MAX_PWMs);
}

// ################### Assignment functions ######################
// Motor pins configuration
void AddMotorDriverPins(int PWM_PINs[4], int DIR_PINs[4], bool REVs[4]) {
  // Motor PWM pins
  this->MOTOR_PWM_PINs = PWM_PINs
  // Motor direction pins
  this->MOTOR_DIRECTION_PINs = DIR_PINs
  // Reverse directions of the wheel
  this->REVERSE_DIRECTIONs = REVs
  // Initialize every wheel
  for (int i = 0; i < 4; i ++) {
    // PWM is output
    pinMode(MOTOR_PWM_PINs[i], OUTPUT);
    // Direction is digital out
    pinMode(MOTOR_DIRECTION_PINs[i], OUTPUT);
    // Write default values
    analogWrite(MOTOR_PWM_PINs[i], 0);           // Stop motor
    digitalWrite(MOTOR_DIRECTION_PINs[i], LOW);  // Reverse direction
  }
}
// Motor pins configuration
void AddMotorDriverPins(int PWM_PINs[4], int DIR_PINs[4]) {
  // By default, it's assumed that you have conected all correctly
  bool REVs[4] = {false, false, false, false};
  // Call the default function for this
  this->AddMotorDriverPins(PWM_PINs, DIR_PINs, REVs);
}
// MAG_Limit
void AddMotorMAGLimit(int MAX_PWMs[4]) {
  // Magnitude limits on wheels
  this->MOTOR_MAX_PWMs = MAX_PWMs
}
// MAG_Limit
void AddMotorMAGLimit(int MAX_PWM) {
  int MAX_PWMs[4] = {MAX_PWM, MAX_PWM, MAX_PWM, MAX_PWM}
  // Call the default function for this
  this->AddMotorMAGLimit(MAX_PWMs);
}

// ##################### Motion functions #######################
// Move bot with PWM at an angle (in degrees)
void Move(int PWM, float angle_degrees) {
  // Convert to radians
  float angle = angle_degrees * PI / 180.0;
  // Main motion
  this->MovePWM_Angle(PWM, angle)
}
// Move bot with PWM at an angle (in radians)
void MovePWM_Angle(int PWM, float angle) {
  /*
    The motion is :
      Top right wheel : Sine coefficient
      Top left wheel : -Cosine coefficient
      Bottom left wheel : -Sine coefficient
      Bottom right wheel : Cosine coefficient
    These parameters are tuned seeing the orientation of wheels
    If REVERSE_DIRECTIONs[i] is true, multiply the result by -1
    If any result is -ve give LOW to the direction pin, else HIGH
  */
  int PWM_vector[4] = {
    PWM * sin(angle),
    -1 * PWM * cos(angle),
    -1 * PWM * sin(angle),
    PWM * cos(angle)
  };
  for (int i = 0; i < 4; i++) {
    MoveMotor(i, PWM_vector[i])
  }
}
// Move individual motor
void MoveMotor(int motor_index, int PWM_vector) {
  // Absolute value to write
  int PWM_val = abs(PWM_vector);
  // Set directions
  if ((PWM_vector > 0 && REVERSE_DIRECTIONs[motor_index] == false) || (PWM_vector < 0 && REVERSE_DIRECTIONs[motor_index] == true)) {
    digitalWrite(MOTOR_DIRECTION_PINs[motor_index], HIGH);
  } else {
    digitalWrite(MOTOR_DIRECTION_PINs[motor_index], LOW);
  }
  analogWrite(MOTOR_PWM_PINs[motor_index], PWM_val);
}
