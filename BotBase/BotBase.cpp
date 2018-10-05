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
    String msg = "Number of wheels set to ";
    msg.concat(number);
    this->debugger.print(DEBUG, msg);
}
// Constructors
BotBase::BotBase() {
    // Nothing here
}
BotBase::BotBase(bool maxMode, int maxModeValue) {
    // Set the max mode on or off
    this->configureMaxModeTo(maxMode, maxModeValue);
}
// Configure motor driver pins for the base (when only PWM and DIR pins are passed, by default reverseDIRs are all false)
void BotBase::AttachPins(int *PWM_PINs, int *DIR_PINs) {
    // Attach PWM and DIR pins to the motor drivers
    this->PWM_pins = PWM_PINs;
    this->DIR_pins = DIR_PINs;
    for (int i = 0; i < this->NUMBER_OF_WHEELS; i++) {
        // PWM and DIR pins are OUTPUT type
        pinMode(PWM_PINs[i], OUTPUT);
        pinMode(DIR_PINs[i], OUTPUT);
        // Debugger INFO message
        String message = "Motor number ";
        message.concat(i + 1);
        message.concat(" attached to (PWM, DIR): ");
        message.concat(PWM_PINs[i]);
        message.concat(", ");
        message.concat(DIR_PINs[i]);
        message.concat(" Reverse DIR: ");
        message.concat(this->reverseDIRs[i] ? "TRUE" : "FALSE");
        // Ex = Motor 1 attached to (PWM, DIR): 45, 5
        this->debugger.print(INFO, message);
    }
}
void BotBase::AttachPins(int *PWM_PINs, int *DIR_PINs, bool *reverseDIRs) {
    // Direction configuration first
    this->reverseDIRs = reverseDIRs;
    // Attach PWM_PINs and DIR_PINs 
    this->AttachPins(PWM_PINs, DIR_PINs);
}
void BotBase::configureMaxModeTo(bool value, int DIR_mag_value) {
    // Configuration of MaxMode
    this->maxMode = value;               // Enable or disable it
    this->maxModeValue = DIR_mag_value;  // Value to give to the PWM pin if maxMode is ON
    String msg = "Max mode set to ";
    msg.concat(value?"TRUE":"FALSE");
    msg.concat(" Magnitude : ");
    msg.concat(this->maxModeValue);
    this->debugger.print(INFO, msg);
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
}
// Move motor i on the bot
void BotBase::MoveMotor(int i) {
    // PWM and DIR values
    int PWM;
    bool DIR;
    if (!this->maxMode) {
        /* Standard 
            PWM connected to PWM of motor driver
            DIR connected to DIR of motor driver
                Direct connection here
        */
        PWM = this->PWM_values[i];   // PWM 
        DIR = this->reverseDIRs[i] ^ this->DIR_values[i];   // DIR : If reverseDIRs is true, then toggle DIR_value
        // Write the values on pins
        // PWM
        analogWrite(this->PWM_pins[i], PWM);
        // Direction
        digitalWrite(this->DIR_pins[i], DIR);
    } else if (this->maxMode) {
        /* MaxMode 
            PWM connected to the DIR pin of motor driver
            PWM pin of motor driver is given a constant HIGH voltage
        */
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
        // PWM pin gets the maxModeValue
        analogWrite(this->PWM_pins[i], this->maxModeValue);
    }
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
