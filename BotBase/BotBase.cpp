/*
  BotBase.cpp - Library to deal with all kinds of bot bases RM deals with
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/
// Including library
#include "BotBase.h"

// ################# Parent class : BotBase #######################
// Set number of wheels
void BotBase::setNumberOfWheelsTo(int number) {
    // Number of wheels passed
    this->NUMBER_OF_WHEELS = number;
}
// Constructors
BotBase::BotBase() {
    // Nothing here
}
BotBase::BotBase(String name, HardwareSerial *debugger_serial, int Level) {
    // Initializer function already implemented
    this->Initialize(name, debugger_serial, Level);
}
// Initializer
void BotBase::Initialize(String name, HardwareSerial *debugger_serial, int Level) {
    // Name of bot
    this->name = name;
    // Debugger serial of bot
    this->botDebuggerSerial = debugger_serial;
    // Priority level of the debugger
    this->debuggerPriorityLevel = Level;
}
// Debugger prioriy level adjustment
void BotBase::SetDebuggerPriorityToLevel(int minLevel) {
    this->debuggerPriorityLevel = minLevel;
}
// Configure motor driver pins for the base
void BotBase::AddMotorDriverPins(int *PWM_PINs, int *DIR_PINs) {
    // Attach PWM and DIR pins to the motor drivers
    this->PWM_pins = PWM_PINs;
    this->DIR_pins = DIR_PINs;
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        // PWM and DIR pins are OUTPUT type
        pinMode(PWM_PINs[i], OUTPUT);
        pinMode(DIR_PINs[i], OUTPUT);
        // Debugger level is 1 (lowest priority)
        String message = "Motor ";
        message.concat(i + 1);
        message.concat(" attached to (PWM, DIR): ");
        message.concat(PWM_PINs[i]);
        message.concat(", ");
        message.concat(DIR_PINs[i]);
        // Ex = Motor 1 attached to (PWM, DIR): 45, 5
        this->DebuggerOutput(2, message);
    }
}
// Move the bot with speed PWM at angle 'angle_degrees'
void BotBase::Move(int PWM, int angle_degrees) {
    // Convert angle to radians
    float angle_radians = angle_degrees * PI/180.0;
    // Use the default move function
    this->Move_PWM_Angle(PWM, angle_radians);
}
// Move motor i on the bot
void BotBase::MoveMotor(int i) {
    // PWM
    analogWrite(this->PWM_pins[i], this->PWM_values[i]);
    // Direction
    digitalWrite(this->DIR_pins[i], this->DIR_values[i]);
    // Send message on terminal
    // Motor %i+1% status = [3: 123, 7: HIGH]
    String message = "Motor ";
    message.concat(i + 1);
    message.concat(" status = [");
    message.concat(this->PWM_pins[i]);
    message.concat(": ");
    message.concat(this->PWM_values[i]);
    message.concat(", ");
    message.concat(this->DIR_pins[i]);
    message.concat(": ");
    message.concat(this->DIR_values[i]);
    message.concat("]");
    this->DebuggerOutput(1, message);
}
// Debugger output function
void BotBase::DebuggerOutput(int level, String output) {
    // If the message priority is less, then no need to display
    if (this->debuggerPriorityLevel > level) {
        return;
    }
    // Print the message on serial monitor in fashion
    // $%name%$:L%level%: %output%
    this->botDebuggerSerial->print("$");
    this->botDebuggerSerial->print(this->name);
    this->botDebuggerSerial->print("$:L");
    this->botDebuggerSerial->print(level);
    this->botDebuggerSerial->print(": ");
    this->botDebuggerSerial->print(output);         // Main message
    this->botDebuggerSerial->println("");
}
