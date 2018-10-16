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

// Motor driver modes
#define MODE_SM 0    // Sign magnitude mode
#define MODE_LAP 1   // Locked anti-phase mode

class BotBase {
protected:
    // ######################### Parts of the base #########################
    int NUMBER_OF_WHEELS;       // Number o wheels
    int *PWM_pins;              // PWM Pin array
    int *PWM_values;            // PWM array written to PWM pins
    int *DIR_pins;              // DIR Pin array
    int *DIR_values;            // DIR array written to DIR pins
    // --------------------- Configurations ------------------------
    bool *reverseDIRs;          // Reverse the directions on the motor driver (motor connections are reversed if true)
    // Motor mode configuration
    int *motorModes;            // Modes of each motor driver attached
    bool modesAttached;         // Modes attached or not
    int LAP_PWM_value;          // Locked anti-phase PWM value (to be given to the PWM pin of motor driver)
    // ##################### Private funcions ####################
    // Set number of wheels
    void setNumberOfWheelsTo(int number);
    // Functions to convert Vector to PWM and DIR values
    void VectorTo_PWM_DIR(int *vector);     
public:
    // ################## Debugger Section ########################
    DebuggerSerial debugger;
    // ##################### Initializer functions ####################
    // Constructors
    BotBase();
    // Configure motor driver pins
    void AttachPins(int *PWM_pins, int *DIR_PINs);         // PWM and DIR
    void AttachPins(int *PWM_pins, int *DIR_PINs, bool *reverseDIRs);   // PWM, DIR and reverse DIR array
    // Configure Mode
    void ConfigureModes(int *modes);                        // Max mode configuration
    void setLAP_PWMto(int PWM_value);
    // ######################### Motion funcions #########################
    // Motion of the bot : Every bot has a Move function (angle in radians)
    virtual void Move_PWM_Angle(int PWM, float angle, float w = 0) = 0;
    // Main motion code called by user
    void Move(int PWM, int angle_degrees, float w = 0);
    // Move motor function
    void MoveMotor(int motor_number);
};

#endif
