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
    // Debugger message (Level: DEBUG)
    // Number of wheels set to %number%
    // Examples:
    // Number of wheels set to 4
    // Number of wheels set to 3
    String msg = "Number of wheels set to ";
    msg.concat(number);
    this->debugger.print(DEBUG, msg);
}
// Constructors
BotBase::BotBase() {
    // Nothing here
    this->modesAttached = false;
}
BotBase::BotBase(int *modes) : BotBase() {
    this->ConfigureModes(modes);
}
// Configure motor modes
void BotBase::ConfigureModes(int *modes) {
    this->motorModes = modes;   // Motor modes
    this->modesAttached = true; // Attached
}
// Configure motor driver pins for the base (when only PWM and DIR pins are passed, by default reverseDIRs are all false)
void BotBase::AttachPins(int *PWM_PINs, int *DIR_PINs) {
    // Attach PWM and DIR pins to the motor drivers
    this->PWM_pins = PWM_PINs;
    this->DIR_pins = DIR_PINs;
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        // PWM and DIR pins are OUTPUT type
        pinMode(this->PWM_pins[i], OUTPUT);
        pinMode(this->DIR_pins[i], OUTPUT);
        // Debugger message (Level: INFO)
        // Motor number %index + 1% attached to (PWM, DIR): %PWM_pin%, %DIR_PINs% Reverse DIR: %reverseDIRs[index]%
        // Examples:
        // Motor number 1 attached to (PWM, DIR): 5, 7 Reverse DIR: FALSE
        // Motor number 2 attached to (PWM, DIR): 6, 8 Reverse DIR: TRUE
        String message = "Motor number ";
        message.concat(i + 1);
        message.concat(" attached to (PWM, DIR): ");
        message.concat(this->PWM_pins[i]);
        message.concat(", ");
        message.concat(this->DIR_pins[i]);
        message.concat(" Reverse DIR: ");
        message.concat(this->reverseDIRs[i] ? "TRUE" : "FALSE");
        this->debugger.print(INFO, message);        // Publish debugger message
    }
    // Debugger message (Level: DEBUG)
    this->debugger.print("All pins attached", DEBUG);
}
// Attach even reverseDIRs as well
void BotBase::AttachPins(int *PWM_PINs, int *DIR_PINs, bool *reverseDIRs) {
    // Direction configuration first
    this->reverseDIRs = reverseDIRs;
    // Attach PWM_PINs and DIR_PINs 
    this->AttachPins(PWM_PINs, DIR_PINs);
}
// Mode configuration
void BotBase::ConfigureModes(int *modes) {
    this->motorModes = modes;        // Modes specified
    this->modesAttached = true;      // Mode specifier called
}
// LAP PWM assignment
void BotBase::setLAP_PWMto(int PWM_value) {
    this->LAP_PWM_value = PWM_value;   // PWM value in LAP mode
}
// Function to convert integer vector to PWM and DIR values
void BotBase::VectorTo_PWM_DIR(int *vect) {
    // Dynamic memory allocation for PWM_values and DIR_values
    this->PWM_values = new int[this->NUMBER_OF_WHEELS];   // PWM values
    this->DIR_values = new int[this->NUMBER_OF_WHEELS];   // DIR values
    for (int wheel_number = 0; wheel_number < this->NUMBER_OF_WHEELS; wheel_number++) {
        this->PWM_values[wheel_number] = abs(vect[wheel_number]);
        this->DIR_values[wheel_number] = vect[wheel_number] >= 0 ? HIGH : LOW;
        // Debugger message
        // Vector[%wheel_number%] -> %vect_value% = %PWM%, %DIR%
        // Examples:
        // Vector[1] -> -53 = 53, LOW
        // Vector[3] -> 189 = 189, HIGH
        String msg = "Vector[";
        msg.concat(wheel_number);
        msg.concat("] -> ");
        msg.concat(vect[wheel_number]);
        msg.concat(" = ");
        msg.concat(this->PWM_values[wheel_number]);
        msg.concat(", ");
        msg.concat((this->DIR_values[wheel_number]) ? "HIGH" : "LOW");
        this->debugger.print(msg, DEBUG);
    }    
}
// Move the bot with speed PWM at angle 'angle_degrees'
void BotBase::Move(int PWM, int angle_degrees, float w) {
    // Convert angle from degrees to radians
    float angle_radians = angle_degrees * DEG_TO_RAD;
    // Use the default move function
    this->Move_PWM_Angle(PWM, angle_radians, w);
    // Call the MoveMotor on every motor (actual actuation of motors)
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        this->MoveMotor(i);     // Move the motor 
    }
    delete [] this->PWM_values;   // Remove the dynamic memory
    delete [] this->DIR_values;   
}
// Move motor i on the bot
void BotBase::MoveMotor(int i) {
    // PWM and DIR values
    int PWM;
    bool DIR;
    // Debugger message (Level: DEBUG)
    // Mode: %mode%
    // For example:
    // Mode: Standard
    // Mode: MaxMode
    String msg = "Mode: ";
    if (!this->modesAttached || this->motorModes[i] == MODE_SM) {
        /* Standard : Sign magnitude mode (default mode)
            PWM connected to PWM of motor driver
            DIR connected to DIR of motor driver
                Direct connection here
        */
        msg.concat("Sign Magnitude"); // Standard mode
        PWM = this->PWM_values[i];   // PWM 
        DIR = this->reverseDIRs[i] ^ this->DIR_values[i];   // DIR : If reverseDIRs is true, then toggle DIR_value
        // Write the values on pins
        // PWM
        analogWrite(this->PWM_pins[i], PWM);
        // Direction
        digitalWrite(this->DIR_pins[i], DIR);
    } else if (this->motorModes[i] == MODE_LAP) {
        /* Locked Anti Phase
            PWM connected to the DIR pin of motor driver
            PWM pin of motor driver is given a constant HIGH voltage
        */
        msg.concat("Locked Anti Phase"); // MaxMode mode
        DIR = this->reverseDIRs[i] ^ this->DIR_values[i]; // DIR : If reverseDIRs is true, then toggle DIR_value
        PWM = 127;
        // Adjust PWM
        if (DIR == HIGH) {         // Forward
            PWM += this->PWM_values[i]/2;
        } else if (DIR == LOW) {   // Reverse
            PWM -= this->PWM_values[i]/2;
        }
        // Write PWM to DIR pin of motor driver
        analogWrite(this->DIR_pins[i], PWM);
        // LAP Mode PWM value
        analogWrite(this->PWM_pins[i], this->LAP_PWM_value);
    }
    this->debugger.print(msg, DEBUG); // DebuggerSerial message
    // Send message on terminal
    // Motor %i+1% status = [3: 123, 7: HIGH]
    // Debugger message
    String message = "Motor ";
    message.concat(i + 1);
    message.concat(" status = [");
    message.concat(this->PWM_pins[i]);
    message.concat(": ");
    message.concat(PWM);
    message.concat(", ");
    message.concat(this->DIR_pins[i]);
    message.concat(": ");
    message.concat(DIR);
    message.concat("]");
    this->debugger.print(message, DEBUG);
}
