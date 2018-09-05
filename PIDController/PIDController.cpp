// Include headers
#include "PIDController.h"

// ::::::::::::: Constructors ::::::::::::::::::
PIDController::PIDController() {
    // Nothing here
}

PIDController::PIDController(String name, double Kp, double Ki, double Kd) {
    // Name of the controller
    this->attachName(name);
    // Assign constants Kp, Ki and Kd
    this->assignParameters(Kp, Ki, Kd);
}

// ::::::::::::::::::::: Member Functions ::::::::::::::::::::
// Attach parameters
void PIDController::assignParameters(double Kp, double Ki, double Kd) {
    // Assign Kp, Ki and Kd
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    // Debugger output
    String msg = "Kp: ";
    msg.concat(Kp);
    msg.concat(", Ki: ");
    msg.concat(Ki);
    msg.concat(", Kd: ");
    msg.concat(Kd);
    this->DebuggerOutput(1, msg);
}
// Attach name
void PIDController::attachName(String name) {
    // Name assignment
    this->name = name;
    // Debugger output
    String msg = "Name assigned: ";
    msg.concat(name);
    this->DebuggerOutput(1, msg);
}
// Initialize the controller
void PIDController::InitializeDebugger(String name, HardwareSerial* debuggerSerial, int priorityLevel) {
    this->debuggerAttached = true;
    // Name of bot
    this->attachName(name);
    // Debugger Serial
    this->debuggerSerial = debuggerSerial;
    // Priority level
    this->debuggerPriorityLevel = priorityLevel;
}

// Main error calculations part
// Assignment of Set Point
void PIDController::assignSetPoint(double setPointValue) {
    // Assign set point
    this->setPoint = setPointValue;
    // Show the message on terminal
    String msg = "Set point assigned value: ";
    msg.concat(setPointValue);
    this->DebuggerOutput(1, msg);
}
// Assignment of Current Value
void PIDController::assignCurrentValue(double currentValue) {
    // Assign current value
    this->currentValue = currentValue;
    // Show the message on terminal
    String msg = "Current value assigned: ";
    msg.concat(currentValue);
    this->DebuggerOutput(1, msg);
}
// Calculate the final error
void PIDController::calculateError() {
    
}
