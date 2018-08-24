/*
  BotBase.h - Library to deal with all kinds of bot bases RM deals with
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Check for the flag
#ifndef BOTBASE_H
#define BOTBASE_H

// Include Arduino main files
#include "Arduino.h"

class BotBase {
protected:
    // ######################### Parts of the base #########################
    int NUMBER_OF_WHEELS;
    int *PWM_pins;
    int *PWM_values;
    int *DIR_pins;
    int *DIR_values;
    // ################## Important features of every bot ##################
    String name;    // Name of bot
    HardwareSerial *botDebuggerSerial;  // Debugger Serial
    int debuggerPriorityLevel;     // Debugger verbocity level
    // ##################### Private funcions ####################
    // Set number of wheels
    void setNumberOfWheelsTo(int number);
    // ############################ Debugger #############################
    // Debugger output through serial
    void DebuggerOutput(int Level, String output);
public:
    // ##################### Initializer functions ####################
    // Constructors
    BotBase();
    BotBase(String name, HardwareSerial *debugger_serial, int Level);
    // Initializing bot parameters
    void Initialize(String name, HardwareSerial *debugger_serial, int Level);
    // Setting the debugger priority, messages less than this level are not displayed
    void SetDebuggerPriorityToLevel(int minLevel);
    // Configure motor driver pins
    void AddMotorDriverPins(int *PWM_pins, int *DIR_PINs);
    // ######################### Motion funcions #########################
    // Motion of the bot : Every bot has a Move function (angle in radians)
    virtual void Move_PWM_Angle(int PWM, float angle) = 0;
    void Move(int PWM, int angle_degrees);
    void MoveMotor(int motor_number);
};

#endif
