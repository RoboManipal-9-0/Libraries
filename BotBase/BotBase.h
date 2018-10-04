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
#include "DebuggerSerial.h"

class BotBase {
protected:
    // ######################### Parts of the base #########################
    int NUMBER_OF_WHEELS;       // Number o wheels
    int *PWM_pins;              // PWM Pin array
    int *PWM_values;            // PWM array written to PWM pins
    int *DIR_pins;              // DIR Pin array
    int *DIR_values;            // DIR array written to DIR pins
    // MaxMode
    bool maxMode;               // MaxMode for the motor drivers
    int maxModeValue;           // The value given to the PWM pin 
    // ##################### Private funcions ####################
    // Set number of wheels
    void setNumberOfWheelsTo(int number);
public:
    // ################## Debugger Section ########################
    DebuggerSerial debugger;
    // ##################### Initializer functions ####################
    // Constructors
    BotBase();
    BotBase(bool maxMode, int maxModeValue = 255);
    // Configure motor driver pins
    void AddMotorDriverPins(int *PWM_pins, int *DIR_PINs);
    // Configure maxMode
    void configureMaxModeTo(bool value, int DIR_mag_value = 255);
    // ######################### Motion funcions #########################
    // Motion of the bot : Every bot has a Move function (angle in radians)
    virtual void Move_PWM_Angle(int PWM, float angle) = 0;
    void Move(int PWM, int angle_degrees);
    void MoveMotor(int motor_number);
};

#endif
