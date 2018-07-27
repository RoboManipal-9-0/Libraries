/*
  BotBase.cpp - Library to deal with all kinds of bot bases RM deals with
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/
// Including derivatives
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
BotBase::BotBase(String name, HardwareSerial *debugger_serial, int baud_rate, int Level) {
    // Initializer function already implemented
    this->Initialize(name, debugger_serial, baud_rate, Level);
}
// Initializer
void Initialize(String name, HardwareSerial *debugger_serial, int baud_rate, int Level) {
    // Name of bot
    this->name = name;
    // Debugger serial of bot
    this->botDebuggerSerial = debugger_serial;
    this->botDebuggerSerial->begin(baud_rate);
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
    for (int i = 0; i <= this->NUMBER_OF_WHEELS; i++) {
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
void BotBase::Move(int PWM, float angle_degrees) {
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


// ###################### Derived class : BotBase #######################
FourSBase::FourSBase() {
    // 4 wheel bot
    this->setNumberOfWheelsTo(4);
}
// Add motor driver pins
void FourSBase::AddMotorDriverPins(int *PWM_PINs, int *DIR_PINs, bool *reverseDIRs) {
    // Call the function of super class and assign PWM, DIR pins
    this->AddMotorDriverPins(PWM_PINs, DIR_PINs);
    // Assign reverse directions
    this->reverseDIRs = reverseDIRs;
    // Debugger output
    String message = "Wheel Reverse DIRs : ";
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        message.concat(this->reverseDIRs[i]);
        message.concat(" ");
    }
    this->DebuggerOutput(2, message);
}
// Motion code (angle in radians)
void FourSBase::Move_PWM_Angle(int PWM, float angle) {
    // PWM vector created from directions
    int PWM_vector[4] = {
        PWM * sin(angle),
        -1 * PWM * cos(angle),
        -1 * PWM * sin(angle),
        PWM * cos(angle)
    };
    // Get the DIR_values vector from PWM_vector and get PWM_values
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        if (PWM_vector[i] >= 0) {
            // If vector > 0, then direction pin must be HIGH
            this->DIR_values[i] = HIGH;
            this->PWM_values[i] = PWM_vector[i];
        } else {
            // If vector < 0, then direction pin must be LOW
            this->DIR_values[i] = LOW;
            this->PWM_values[i] = -PWM_vector[i];
        }
        if (this->reverseDIRs) {
            // Reverse the direction if motor is wired in reverse
            this->DIR_values = !(this->reverseDIRs);
        }
        // Tell the motor to move
        this->MoveMotor(i);
    }
}
