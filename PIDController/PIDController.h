/*
  PIDController.h - Library to deal with PID controller (Step input)
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Check for flag
#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

// Include basic libraries
#include "Arduino.h"

// Main class
class PIDController {
    // ================ Variables ================
    // ----------- Controller variables ------------------
    double Kp, Kd, Ki;    // PID proportionality constants
    double setPoint;      // Set point (target value)
    double currentValue;  // Current value of the signal
    double previousValue; // Previous value of the signal
    double currentErrorValue;                   // Current error value
    double previousErrorValue;              // Previous error value
    double part_Kp, part_Kd, part_Ki;    // Three components of PID
    // Activate
    bool controlActive;                 // Use the controller or deactivate it
    // ------------------ Debugger ----------------------
    String name;                    // Name of the bot
    HardwareSerial *debuggerSerial; // Hardware Serial
    int debuggerPriorityLevel;      // Priority level
    // ================ Functions ================
    double calculateError();

public:
    PIDController(String name, float Kp, float Ki, float Kd);

};


#endif
