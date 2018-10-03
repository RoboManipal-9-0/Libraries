/*
    DebuggerSerial.h - Library for DebuggerSerial
    Copyright (c) 2018 RoboManipal. All right reserved
    File created by : Avneesh Mishra
    Last commit done by : Avneesh Mishra
*/

// Check for the flag
#ifndef DEBUGGERSERIAL_H
#define  DEBUGGERSERIAL_H

// Arduino main files
#include "Arduino.h"

// Debugger Levels
#define SENSOR_FEED 0
#define DEBUG 1
#define INFO 2
#define WARN 3
#define ERROR 4
#define FATAL 5

class DebuggerSerial {
protected:
    // ########### Main parts of DebuggerSerial #############
    Stream *debuggerSerial;     // Main serial
    String name;    // Name of the debugger
    int debuggerPriorityLevel;    // The priority level of debugger
    bool debuggerEnabled;         // Enable the debugger
    bool debuggerSerialDefined;   // If the debuggerSerial is defined
    // ############## Private functions ###################
    void DebuggerOutput(int Level, String output);   // One stop for all output to debuggerSerial
public:
    // ################ Initializer functions ###############
    // ----------------- Constructors ----------------------
    DebuggerSerial();     // Empty constructor
    DebuggerSerial(String name);    // Name only
    DebuggerSerial(Stream *debuggerSerial);   // DebuggerSerial only
    DebuggerSerial(int priorityLevel);   // Priority level
    DebuggerSerial(String name, int priorityLevel);  // Name and priority
    DebuggerSerial(String name, Stream *debuggerSerial); // Name and serial
    // All 3 in one
    DebuggerSerial(String name, Stream *debuggerSerial, int priorityLevel);
    // Standalone initializers
    // All 3
    void Initialize(String name, Stream *debuggerSerial, int priorityLevel);
    void InitializeName(String name);            // Name
    void AttachSerial(Stream *debuggerSerial);   // DebuggerSerial
    void SetDebuggerPriorityToLevel(int minLevel);  // Level
    void Initialize(Stream *debuggerSerial, int priorityLevel);  // Serial and priorityLevel
    // ----------------- Print messages to debuggerSerial -----------------
    void printMessage(int level, String output);    // Print message
    void print(int level, String output);           // Print message
    void print(String output, int level);           // Print, order or args reversed
    void printSensorData(double value);             // Println the value as SENSOR_FEED level
};

#endif
