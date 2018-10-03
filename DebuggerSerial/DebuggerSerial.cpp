/*
    DebuggerSerial.cpp - Library for DebuggerSerial
    Copyright (c) 2018 RoboManipal. All right reserved
    File created by : Avneesh Mishra
    Last commit done by : Avneesh Mishra
*/

// Include header file
#include "DebuggerSerial.h"

// Convert the number to string for output
String PriorityLevelName(int priorityLevel) {
    switch(priorityLevel) {
        case SENSOR_FEED:
            return "SENSOR_FEED";
        break;
        case NOTIFICATION:
            return "NOTIFICATION";
        break;
        case DEBUG:
            return "DEBUG";
        break;
        case INFO:
            return "INFO";
        break;
        case WARNING:
            return "WARNING";
        break;
        case ERROR:
            return "ERROR";
        break;
        case FATAL:
            return "FATAL";
        break;
        default:
            return "<NULL>";
        break;
    }
}

/*
    ---------- Main class : DebuggerSerial -----------
    ##################################################
    ############### Public functions #################
    ##################################################
*/

// ############ Constructors ###############
DebuggerSerial::DebuggerSerial() {
    // Empty constructor
}
DebuggerSerial::DebuggerSerial(String name) : DebuggerSerial() {
    // Initialize name using the InitializeName parameter
    this->InitializeName(name);
}
DebuggerSerial::DebuggerSerial(Stream *debuggerSerial) : DebuggerSerial() {
    // Attach the debugger serial
    this->AttachSerial(debuggerSerial);
}
DebuggerSerial::DebuggerSerial(int priorityLevel) : DebuggerSerial() {
    // Assign the priority level
    this->SetDebuggerPriorityToLevel(priorityLevel);
}
DebuggerSerial::DebuggerSerial(String name, int priorityLevel) : DebuggerSerial(name)
{
    // Assign a priority level
    this->SetDebuggerPriorityToLevel(priorityLevel);
}
DebuggerSerial::DebuggerSerial(String name, Stream *debuggerSerial): DebuggerSerial(name) {
    // Assign the stream
    this->AttachSerial(debuggerSerial);
}
DebuggerSerial::DebuggerSerial(String name, Stream *debuggerSerial, int priorityLevel) : DebuggerSerial(name, debuggerSerial) {
    // Assign the priority level
    this->SetDebuggerPriorityToLevel(priorityLevel);
}

// ###################### Initializer functions ######################
// ---------------- Initialize functions ----------------
void DebuggerSerial::Initialize(Stream *debuggerSerial, int priorityLevel) {
    // Initialize debugger and set priority
    this->AttachSerial(debuggerSerial);   // Main serial
    this->SetDebuggerPriorityToLevel(priorityLevel);    // Set priority to level
}
void DebuggerSerial::Initialize(String name, Stream *debuggerSerial, int priorityLevel) {
    // Initialize everything
    this->InitializeName(name);
    this->Initialize(debuggerSerial, priorityLevel);
}
// ---------------- Individual initializers ----------------
// Main debugger serial attachment
void DebuggerSerial::AttachSerial(Stream *debuggerSerial) {
    this->debuggerSerial = debuggerSerial;
    this->debuggerSerialDefined = true;
    this->enableDebugger();
    this->RaiseNotification("DebuggerSerial attached");
}
// Name initializer
void DebuggerSerial::InitializeName(String name) {
    // Initialize the name of debugger
    this->name=name;
    // Debugger
    String msg = "Debugger name initialized to ";
    msg.concat(this->name);
    this->RaiseNotification(msg);
}
void DebuggerSerial::SetDebuggerPriorityToLevel(int priorityLevel) {
    this->debuggerPriorityLevel = priorityLevel;
    String msg = "Debugger set to ";
    msg.concat(PriorityLevelName(priorityLevel));
    this->RaiseNotification(msg);
}

// ###################### Settings ######################
// Enable and disable the debugger
void DebuggerSerial::enableDebugger() {
    this->debuggerEnabled = true;
    this->RaiseNotification("Debugger enabled");
}
void DebuggerSerial::disableDebugger() {
    this->RaiseNotification("Debugger disabled");
    this->debuggerEnabled = false;
}
// ########## Print messages to DebuggerSerial ############
void DebuggerSerial::printMessage(int level, String output) {
    this->DebuggerOutput(level, output);      // DebuggerOutput function
}
void DebuggerSerial::printSensorData(double value) {
    // Print the sensor data as string
    String msg = "";
    msg.concat(value);
    this->printMessage(NOTIFICATION, msg);
}
void DebuggerSerial::print(int level, String output) {
    this->printMessage(level, output);
}
void DebuggerSerial::print(String output, int level) {
    this->print(level, output);
}



/*
    ---------- Main class : DebuggerSerial -----------
    ##################################################
    ############### Private functions ################
    ##################################################
*/

void DebuggerSerial::DebuggerOutput(int Level, String output) {
    // ################# Protocol #################
    // SENSOR_FEED type
    /*
        [TIMESTAMP] $NAME$ VALUE
    */
    // Notifications
    /*
        [TIMESTAMP] > MESSAGE
    */
    // Debug and above
    /* 
        [TIMESTAMP LEVEL] $NAME$ MESSAGE
    */
    // Timestamp part 
    String msg = "[";
    msg.concat(millis());
    if (Level == NOTIFICATION && Level == SENSOR_FEED) {
        msg.concat("]");
    } else {
        msg.concat(" ");
        msg.concat(PriorityLevelName(Level));
        msg.concat("]");
    }
    // Modifier part (> or NAME)
    if (Level == NOTIFICATION) {
        msg.concat(">");
    } else {
        msg.concat("$");
        msg.concat(this->name);
        msg.concat("$");
    }
    msg.concat(" ");
    // Actual message / output
    msg.concat(output);
}
void DebuggerSerial::RaiseNotification(String message) {
    this->DebuggerOutput(NOTIFICATION, message);
}