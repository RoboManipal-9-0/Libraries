/*
  S4Base.h - Library for controlling a four wheel bot having an S type
             wheel configuration.
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Including directives
#include "S4Base.h"

// ################## SETUP FUNCTIONS #######################
// Empty constructor
S4Base::S4Base() {
  // Do nothing
}
// Assignment constructor
S4Base::S4Base(int MOTOR_PINs[4], int DIR_PINs[4], bool REV_DIRs[4], int MAX_PWMs[4]) {
  // Assignment of motor pin connections
  this->AddMotorDriverPins(MOTOR_PWMs, DIR_PINs, REV_DIRs);
  // Assignment of Max magnitude
  this->AddMotorMAGLimit(MAX_PWMs);
}

// ################### Assignment functions ######################
// Information about the base
// Initialize the base module
// Initializer for name, debugger and Level
void S4Base::Initialize(String name, HardwareSerial *debugger, int Level) {
  // Assigning the name
  this->name = name;
  // Debugger
  this->debuggerSerial = debugger;
  this->debuggerSerial->begin(57600);
  // Level
  this->DEBUGGER_LEVEL = Level;
}
void S4Base::Initialize(String name, HardwareSerial *debugger) {
  // Go for the default
  int DEFAULT_LEVEL = 3;
  this->Initialize(name, debugger, DEFAULT_LEVEL);
}
// Motor pins configuration
void S4Base::AddMotorDriverPins(int PWM_PINs[4], int DIR_PINs[4], bool REVs[4]) {
  // Initialize every wheel
  for (int i = 0; i < 4; i ++) {
    // Motor PWM pins
    this->MOTOR_PWM_PINs[i] = PWM_PINs[i];
    // Motor direction pins
    this->MOTOR_DIRECTION_PINs[i] = DIR_PINs[i];
    // Reverse directions of the wheel
    this->REVERSE_DIRECTIONs[i] = REVs[i];
    // PWM is output
    pinMode(MOTOR_PWM_PINs[i], OUTPUT);
    // Direction is digital out
    pinMode(MOTOR_DIRECTION_PINs[i], OUTPUT);
    // Write default values
    analogWrite(MOTOR_PWM_PINs[i], 0);           // Stop motor
    digitalWrite(MOTOR_DIRECTION_PINs[i], LOW);  // Reverse direction
  }
}
// Motor pins configuration
void S4Base::AddMotorDriverPins(int PWM_PINs[4], int DIR_PINs[4]) {
  // By default, it's assumed that you have conected all correctly
  bool REVs[4] = {false, false, false, false};
  // Call the default function for this
  this->AddMotorDriverPins(PWM_PINs, DIR_PINs, REVs);
}
// MAG_Limit
void S4Base::AddMotorMAGLimit(int MAX_PWMs[4]) {
  // Magnitude limits on wheels
  for (int i = 0; i < 4; i++) {
    this->MOTOR_MAX_PWMs[i] = MAX_PWMs[i];
  }
}
// MAG_Limit
void S4Base::AddMotorMAGLimit(int MAX_PWM) {
  int MAX_PWMs[4] = {MAX_PWM, MAX_PWM, MAX_PWM, MAX_PWM};
  // Call the default function for this
  this->AddMotorMAGLimit(MAX_PWMs);
}

// ##################### Motion functions #######################
// Move bot with PWM at an angle (in degrees)
void S4Base::Move(int PWM, float angle_degrees) {
  // Convert to radians
  float angle = angle_degrees * PI / 180.0;
  // Main motion
  this->MovePWMAngle(PWM, angle);
  // Show on serial
  String description = "Moving at PWM ";
  description.concat(PWM);
  description.concat(" angle ");
  description.concat(angle_degrees);
  this->DebuggerOutput(2, description);
}
// Move bot with PWM at an angle (in radians)
void S4Base::MovePWMAngle(int PWM, float angle) {
  /*
    The motion is :
      Top right wheel : Sine coefficient
      Top left wheel : -Cosine coefficient
      Bottom left wheel : -Sine coefficient
      Bottom right wheel : Cosine coefficient
    These parameters are tuned seeing the orientation of wheels
    If REVERSE_DIRECTIONs[i] is true, multiply the result by -1
    If any result is -ve give LOW to the direction pin, else HIGH
  */
  int PWM_vector[4] = {
    PWM * sin(angle),
    -1 * PWM * cos(angle),
    -1 * PWM * sin(angle),
    PWM * cos(angle)
  };
  for (int i = 0; i < 4; i++) {
    this->MoveMotor(i, PWM_vector[i]);
  }
}
// Move individual motor
void S4Base::MoveMotor(int motor_index, int PWM_vector) {
  // Absolute value to write
  int PWM_val = abs(PWM_vector);
  // Set directions
  if (PWM_vector > 0 && REVERSE_DIRECTIONs[motor_index] == false) {
    // Move the wheel in +ve direction
    digitalWrite(MOTOR_DIRECTION_PINs[motor_index], HIGH);
  } else if (PWM_vector < 0 && REVERSE_DIRECTIONs[motor_index] == true) {
    // Move the wheel in -ve direction (reversed direction)
    digitalWrite(MOTOR_DIRECTION_PINs[motor_index], HIGH);
  } else {
    digitalWrite(MOTOR_DIRECTION_PINs[motor_index], LOW);
  }
  analogWrite(MOTOR_PWM_PINs[motor_index], PWM_val);
  // Write on serial
  String debugger = "";
  debugger.concat(PWM_val);
  debugger.concat(" written to pin ");
  debugger.concat(MOTOR_PWM_PINs[motor_index]);
  this->DebuggerOutput(3, debugger);
}

// ##################### Debugger functions #######################
// Put something on serial
void S4Base::DebuggerOutput(int Level, String output) {
  // If DEBUGGER_LEVEL < Level, then this message is not needed on serial monitor
  if (this->DEBUGGER_LEVEL < Level) {
    // No need to get this verbose
    return;
  }
  // Print debugger message ==> $name$ - L$N$ : $output$
  this->debuggerSerial->print("$ ");
  this->debuggerSerial->print(this->name);
  this->debuggerSerial->print(" - L");
  this->debuggerSerial->print(Level);
  this->debuggerSerial->print(" : ");
  this->debuggerSerial->print(output);
  this->debuggerSerial->println("");
}
// Print something to serial
void S4Base::DebuggerOutput(String output) {
  // Defaul level for debugger
  int DEFAULT_LEVEL = 3;
  this->DebuggerOutput(DEFAULT_LEVEL, output);
}
