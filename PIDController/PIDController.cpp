// Include headers
#include "PIDController.h"

// ::::::::::::: Constructors ::::::::::::::::::
PIDController::PIDController() {
    // Assign an accumulation factor of 0.5 (for KI)
    this->setAccFactor(0.5, 0.5);
}

PIDController::PIDController(double Kp, double Ki, double Kd) : PIDController() {
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
    // Debugger message (Level: INFO)
    // Kp: %Kp%, Ki: %Ki%, Kd: %Kd%
    // For example:
    // Kp: 0.7, Ki: 0.0001, Kd: 0.08
    // Kp: 0.4, Ki: 0, Kd: 0.09
    String msg = "Kp: ";
    msg.concat(Kp);
    msg.concat(", Ki: ");
    msg.concat(Ki);
    msg.concat(", Kd: ");
    msg.concat(Kd);
    this->debugger.print(INFO, msg);
}
void PIDController::assignPIDParameters(double Kp, double Ki, double Kd) {
    this->assignParameters(Kp, Ki, Kd);
}
// Accumulator factor
void PIDController::setAccFactor(double newValuePast, double newValuePresent) {
    // Debugger message (Level: INFO)
    // Accumulation factors updated {Past: %old_accFactorPast% to %new_accFactorPast%, Present: %old_accFactorPresent% to %new_accFactorPresent%}
    // For example:
    // Accumulation factors updated {Past: 0.003 to 0.004, Present: 0.070 to 0.050}
    // Accumulation factors updated {Past: 0.010 to 0.009, Present: 0.060 to 0.090}
    String msg = "Accumulation factors updated {Past: ";
    msg.concat(this->accFactorPast);
    msg.concat(" to ");
    // Set new accumulation factor (updating factor) for the past
    this->accFactorPast = newValuePast;
    msg.concat(this->accFactorPast);
    msg.concat(", Present: ");
    msg.concat(this->accFactorPresent);
    msg.concat(" to ");
    // Set new accumulation factor (updating factor) for the present
    this->accFactorPresent = newValuePresent;
    msg.concat(this->accFactorPresent);
    msg.concat("}");
    // Debugger
    this->debugger.print(INFO, msg);
}
// Main error calculations part
// Assignment of Set Point
void PIDController::assignSetPoint(double setPointValue) {
    // Assign set point
    this->setPoint = setPointValue;
    // Show the message on terminal
    // Debugger message (Level: DEBUG)
    // Set point value assigned: %setPointValue%
    // For example:
    // Set point value assigned: 35.5
    // Set point value assigned: 60
    String msg = "Set point value assigned: ";
    msg.concat(this->setPoint);
    this->debugger.print(DEBUG, msg);
}
// Assignment of Current Value
void PIDController::assignCurrentValue(double currentValue) {
    // Assign current value
    this->currentValue = currentValue;
    // Show the message on terminal
    // Debugger message (Level: DEBUG)
    // Current value assigned: %currentValue%
    // For example: 
    // Current value assigned: 20
    // Current value assigned: 90
    String msg = "Current value assigned: ";
    msg.concat(this->currentValue);
    this->debugger.print(DEBUG, msg);
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
    // Debugger message (Level: DEBUG)
    // Errors (P, D and I): %Ep%, %Ed%, %Ei%
    // For example:
    // Errors (P, D and I): 10, -0.5, 0.03
    // Errors (P, D and I): 25, -0.9, 0.09
    String msg = "Errors (P, D and I): ";
    msg.concat(this->currentErrorValue);
    msg.concat(", ");
    msg.concat(this->currentErrorValue - this->previousErrorValue);
    msg.concat(", ");
    msg.concat(this->accumulatedError);
    this->debugger.print(DEBUG, msg);
}
// Kp part
void PIDController::calculate_Kp_error() {
    this->part_Kp = this->Kp * this->currentErrorValue;
    // Debugger messages (Level: DEBUG)
    // Kp_Error: %Kp% * %currentErrorValue% = %part_Kp%
    // For example:
    // Kp_Error: 0.7 * 10 = 7
    // Kp_Error: 0.4 * 25 = 10
    String msg = "Kp_Error: ";
    msg.concat(this->Kp);
    msg.concat(" * ");
    msg.concat(this->currentErrorValue);
    msg.concat(" = ");
    msg.concat(this->part_Kp);
    this->debugger.print(DEBUG, msg);
}
// Kd part
void PIDController::calculate_Kd_error() {
    double differentialError = (this->currentErrorValue - this->previousErrorValue);
    this->part_Kd = this->Kd * differentialError;
    // Debugger message (Level: DEBUG)
    // Kd_Error: %Kd% * %differentialError% = %part_Kd%
    // For example:
    // Kd_Error: 0.08 * -0.5 = -0.04
    // Kd_Error: 0.09 * -0.9 = -0.081
    String msg = "Kd_Error: ";
    msg.concat(this->Kd);
    msg.concat(" * ");
    msg.concat(this->currentErrorValue - this->previousErrorValue);
    msg.concat(" = ");
    msg.concat(this->part_Kd);
    this->debugger.print(DEBUG, msg);
}
// Ki part
void PIDController::calculate_Ki_error() {
    this->part_Ki = this->Ki * this->accumulatedError;
    // Debugger message (Level: DEBUG)
    // Ki_Error: %Ki% * %accumulatedError% = %part_Ki%
    // For example:
    // Ki_Error: 0.001 * 45 = 0.045
    // Ki_Error: 0.03 * 10 = 0.3
    String msg = "Ki_Error: ";
    msg.concat(this->Ki);
    msg.concat(" * ");
    msg.concat(this->accumulatedError);
    msg.concat(" = ");
    msg.concat(this->part_Ki);
    this->debugger.print(DEBUG, msg);
}
// Return the total error function
double PIDController::retError() {
    // Return the total error
    this->calculateError();
    this->calculate_Kp_error();
    this->calculate_Ki_error();
    this->calculate_Kd_error();
    double totalError = this->part_Kp + this->part_Ki + this->part_Kd;
    // Debugger message (Level: DEBUG)
    // Total error: %totalError%
    // For example:
    // Total error: 19
    // Total error: -0.05
    String msg = "Total error: ";
    msg.concat(totalError);
    this->debugger.print(DEBUG, msg);
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
    double value = this->currentValue + this->retError();
    // Debugger message (Level: DEBUG)
    // Corrected value: %value%
    // For example:
    // Corrected value: 18
    String msg = "Corrected value: ";
    msg.concat(value);
    this->debugger.print(DEBUG, msg);
    return value;
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
