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
    bool *reverseDIRs;          // Reverse the directions on the motor driver (motor connections are reversed if true)
    // MaxMode
    bool maxMode;               // MaxMode for the motor drivers
    int maxModeValue;           // The value given to the PWM pin 
    // ##################### Private funcions ####################
    // Set number of wheels
    void setNumberOfWheelsTo(int number);
    // Functions to convert Vector to PWM and DIR values
    void VectorTo_PWM_DIR(float *vector);
    void VectorTo_PWM_DIR(int *vector);
    void VectorTo_PWM_DIR_SingleWheel(float vect_value, int wheel_number);
    void VectorTo_PWM_DIR_SingleWheel(int vect_value, int wheel_number);
    // ################## Debugger Section ########################
    DebuggerSerial debugger;
public:
    // ##################### Initializer functions ####################
    // Constructors
    BotBase();
    BotBase(bool maxMode, int maxModeValue = 255);
    // Configure motor driver pins
    void AttachPins(int *PWM_pins, int *DIR_PINs);         // PWM and DIR
    void AttachPins(int *PWM_pins, int *DIR_PINs, bool *reverseDIRs);   // PWM, DIR and reverse DIR array
    // Configure maxMode
    void ConfigureMaxModeTo(bool value, int DIR_mag_value = 255);
    // ######################### Motion funcions #########################
    // Motion of the bot : Every bot has a Move function (angle in radians)
    virtual void Move_PWM_Angle(int PWM, float angle, float w = 0) = 0;
    // Main motion code called by user
    void Move(int PWM, int angle_degrees, float w = 0);
    // Move motor function
    void MoveMotor(int motor_number);
};

#endif
