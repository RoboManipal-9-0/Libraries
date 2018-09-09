// Include headers
#include "PIDController.h"

// ::::::::::::: Constructors ::::::::::::::::::
PIDController::PIDController() {
    // Assign an accumulation factor of 0.5 (for KI)
    this->setAccFactor(0.5, 0.5);
}

PIDController::PIDController(String name, double Kp, double Ki, double Kd) : PIDController() {
    // Name of the controller
    this->attachName(name);
    // Assign constants Kp, Ki and Kd
    this->assignParameters(Kp, Ki, Kd);
}

// ::::::::::::::::::::: Member Functions ::::::::::::::::::::
void PIDController::DebuggerOutput(int level, String message, bool printName = true) {
    // If message priority is lesser, then don't print
    if (this->debuggerPriorityLevel > level || !debuggerAttached) {
        return;
    }
    // Print the message on serial monitor in fashion
    // $%name%$:L%level%: %message%
    this->debuggerSerial->print("$");
    if (printName) {
        this->debuggerSerial->print(this->name);
    }
    else {
        this->debuggerSerial->print("PID_CONTROLLER__NAME");
    }
    this->debuggerSerial->print("$:L");
    this->debuggerSerial->print(level);
    this->debuggerSerial->print(": ");
    this->debuggerSerial->print(message);     // Main message
    this->debuggerSerial->println("");
}

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
    this->DebuggerOutput(LEVEL_INIT, msg);
}
void PIDController::assignPIDParameters(double Kp, double Ki, double Kd) {
    this->assignParameters(Kp, Ki, Kd);
}
// Accumulator factor
void PIDController::setAccFactor(double newValuePast, double newValuePresent) {
    String msg = "Accumulation factor updated from {Past: ";
    msg.concat(this->accFactorPast);
    msg.concat(" to ");
    // Set new accumulation factor (updation factor)
    this->accFactorPast = newValuePast;
    msg.concat(this->accFactorPast);
    msg.concat(", Present: ");
    msg.concat(this->accFactorPresent);
    msg.concat(" to ");
    this->accFactorPresent = newValuePresent;
    msg.concat(this->accFactorPresent);
    msg.concat(" }");
    // Debugger
    this->DebuggerOutput(LEVEL_ASSIGNMENT, msg);
}
// Attach name
void PIDController::attachName(String name) {
    // Name assignment
    this->name = name;
    // Debugger output
    String msg = "Name assigned: ";
    msg.concat(name);
    this->DebuggerOutput(LEVEL_INIT, msg, false);
}
// Initialize the controller
void PIDController::InitializeDebugger(String name, HardwareSerial* debuggerSerial, int priorityLevel) {
    this->InitializeDebugger(debuggerSerial, priorityLevel);
    // Name of bot
    this->attachName(name);
}
void PIDController::InitializeDebugger(HardwareSerial* debuggerSerial, int priorityLevel) {
    this->debuggerAttached = true;
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
    String msg = "Set point value assigned: ";
    msg.concat(setPointValue);
    this->DebuggerOutput(LEVEL_ASSIGNMENT, msg);
}
// Assignment of Current Value
void PIDController::assignCurrentValue(double currentValue) {
    // Assign current value
    this->currentValue = currentValue;
    // Show the message on terminal
    String msg = "Current value assigned: ";
    msg.concat(currentValue);
    this->DebuggerOutput(LEVEL_ASSIGNMENT, msg);
}
// Calculate the error function (difference b/w set and curr)
void PIDController::calculateError() {
    // Previous error value
    this->previousErrorValue = this->currentErrorValue;
    // Current error value (currentErrorValue = ser -current)
    this->currentErrorValue = this->setPoint - this->currentValue;
    // Add to accumulated errors
    this->accumulatedError = this->currentErrorValue * this->accFactorPresent
                             + this->accumulatedError * this->accFactorPast;
    String msg = "Errors (P, D and I): ";
    msg.concat(this->currentErrorValue);
    msg.concat(", ");
    msg.concat(this->currentErrorValue - this->previousErrorValue);
    msg.concat(", ");
    msg.concat(this->accumulatedError);
    this->DebuggerOutput(LEVEL_ERROR_REPORTING, msg);
}
// Kp part
void PIDController::calculate_Kp_error() {
    this->part_Kp = this->Kp * this->currentErrorValue;
    // Debugger
    String msg = "Kp_Error : ";
    msg.concat(this->Kp);
    msg.concat(" * ");
    msg.concat(this->currentErrorValue);
    msg.concat(" = ");
    msg.concat(this->part_Kp);
    this->DebuggerOutput(LEVEL_ERROR_REPORTING, msg);
}
// Kd part
void PIDController::calculate_Kd_error() {
    this->part_Kd = this->Kd * (this->currentErrorValue - this->previousErrorValue);
    // Debugger
    String msg = "Kd_Error : ";
    msg.concat(this->Kd);
    msg.concat(" * ");
    msg.concat(this->currentErrorValue - this->previousErrorValue);
    msg.concat(" = ");
    msg.concat(this->part_Kd);
    this->DebuggerOutput(LEVEL_ERROR_REPORTING, msg);
}
// Ki part
void PIDController::calculate_Ki_error() {
    this->part_Ki = this->Ki * this->accumulatedError;
    // Debugger
    String msg = "Ki_Error : ";
    msg.concat(this->Ki);
    msg.concat(" * ");
    msg.concat(this->accumulatedError);
    msg.concat(" = ");
    msg.concat(this->part_Ki);
    this->DebuggerOutput(LEVEL_ERROR_REPORTING, msg);
}
// Return the total error function
double PIDController::retError() {
    // Return the total error
    this->calculateError();
    this->calculate_Kp_error();
    this->calculate_Ki_error();
    this->calculate_Kd_error();
    double totalError = this->part_Kp + this->part_Ki + this->part_Kd;
    String msg = "Total error : ";
    msg.concat(totalError);
    this->DebuggerOutput(LEVEL_ERROR_REPORTING, msg);
    return totalError;
}
double PIDController::retError(double currentValue) {
    // Assign the current value and the calculate error and return it
    this->assignCurrentValue(currentValue);
    // Error part
    return this->retError();
}
double PIDController::retError(double setPoint, double currentValue) {
    // Assign set point first
    this->assignSetPoint(setPoint);
    // We've already written this code
    return this->retError(currentValue);
}
double PIDController::getCorrectedValue() {
    // Error + current value = corrected value
    return this->currentValue + this->retError();
}
double PIDController::getCorrectedValue(double currentValue) {
    // Set corrected value
    this->assignCurrentValue(currentValue);
    // Get the corrected values
    return this->getCorrectedValue();
}
double PIDController::getCorrectedValue(double setPoint, double currentValue) {
    // Set the setPoint value
    this->assignSetPoint(setPoint);
    // Return main stuff
    return this->getCorrectedValue(currentValue);
}
