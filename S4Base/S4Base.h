/*
  S4Base.h - Library for controlling a four wheel bot having an S type
             wheel configuration.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Check for the flags of class being declared
#ifndef S4Base_H
#define S4Base_H

// Include basic arduino functions
#include "Arduino.h"

// Class code here
class S4Base {
private:
  // Bot observed from top view in S formation
  // Pin configuration
  int MOTOR_PWM_PINs[4];            // Motor PWM connection pins
  int MOTOR_DIRECTION_PINs[4];      // Motor DIR connection pins
  bool REVERSE_DIRECTIONs[4];   // Reverse connections for motor directions
  // Motion of bot
  // Limit for the PWMs of all four motors (as set on 8 bit devices)
  int MOTOR_MAX_PWMs[4];
  // Actual PWM of all motors (current PWM)
  int MOTOR_PWMs[4];
  // Angle of motion of bot
  float ANGLE;          // in radians
  float ANGLE_degrees;  // in degrees
  // Debugger and additional information for the Bot
  String name;          // name of the Bot
  HardwareSerial debuggerSerial;  // HardwareSerial
  int DEBUGGER_LEVEL;

public:
  // ######################  Constructors  #########################
  // Assignment constructor
  S4Base (int motor_pins[4], int dir_pins[4], bool dirs[4], int MAX_PWMs[4]);
  // Default constructor
  S4Base ();
  // ################### Assignment functions ######################
  // Information of base
  void Initialize(String name, HardwareSerial &debugger, int Level);
  void Initialize(String name, HardwareSerial &debugger);
  // Motor pins configuration
  void AddMotorDriverPins(int PWM_PINs[4], int DIR_PINs[4], bool REVs[4]);
  void AddMotorDriverPins(int PWM_PINs[4], int DIR_PINs[4]);
  // MAG_Limit
  void AddMotorMAGLimit(int MAX_PWMs[4]);
  void AddMotorMAGLimit(int MAX_PWM);
  // ##################### Motion functions #######################
  // Move bot with PWM at an angle (in degrees)
  void Move(int PWM, float angle_degrees);
  // Move bot with PWM at an angle (in radians)
  void MovePWMAngle(int PWM, float angle);
  // Move individual motor
  void MoveMotor(int motor_index, int PWM_vector);
  // ######################### DEBUGGER ###########################
  // Debugger output for serial
  void DebuggerOutput(String output);
  void DebuggerOutput(int LEVEL, String output);

};

#endif
