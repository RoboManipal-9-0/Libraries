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
    // :::::::::::::::: Private members :::::::::::::::::::
    // ================ Variables ================
    // ----------- Controller variables ------------------
    double Kp, Kd, Ki;    // PID proportionality constants
    double setPoint;      // Set point (target value)
    double currentValue;  // Current value of the signal
    double previousValue; // Previous value of the signal
    double currentErrorValue;                   // Current error value
    double previousErrorValue;              // Previous error value
    double accumulatedError;                // Total sum value of errors
    double part_Kp, part_Kd, part_Ki;    // Three components of PID
    // Activating the controller (Automatic)
    int activationBuffer;      // Number of samples for which the controller is inactive
    bool controllerRun;        // Use the controller or deactivate it
    bool controllerEnable;     // Manually enable or disable the controller
    // ------------------ Debugger ----------------------
    String name;                    // Name of the bot
    HardwareSerial *debuggerSerial; // Hardware Serial
    bool debuggerAttached;          // If debugger has been attached or not
    int debuggerPriorityLevel;      // Priority level
    // ================ Functions ================
    // Debugger
    void DebuggerOutput(int level, String message);
    // Error values
    void calculateError();        // Main error calculation
    void calculate_Kp_error();    // Proportional error calculation
    void calculate_Kd_error();    // Derivative error calculation
    void calculate_Ki_error();    // Integral error calculation
public:
    // :::::::::::::::::: Public members :::::::::::::::::::::::::::
    // ===================== Constructors ===========================
    // Constructor: Empty constructor
    PIDController();
    // Constructor: Assign name, Kp, Ki and Kd
    PIDController(String name, double Kp, double Ki, double Kd);
    // ===================== Member functions ========================
    // Assignment and return of control signals
    void assignParameters(double Kp, double Ki, double Kd);
    void assignSetPoint(double setPointValue);  // Assign a set point to follow
    void assignCurrentValue(double currentValue); // Assign the current signal value
    double retError(); // Return the error value calculated through the PID algorithm
    double retError(double currentValue);    // Same as retError()
    double retError(double setPoint, double currentValue); // Same as retError()
    double getCorrectedValue();  // Returns the final corrected signal (after controller is applied)
    double getCorrectedValue(double currentValue); // Same as getCorrectedValue()
    double getCorrectedValue(double setPoint, double currentValue); // Same as getCorrectedValue()
    // Assignment and debugger control
    void attachName(String name);   // Assign name
    void InitializeDebugger(HardwareSerial* debuggerSerial, int priorityLevel); // Debugger serial
};


#endif
