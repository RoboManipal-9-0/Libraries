/*
  RazorIMU_9DOF.h - Library to deal with Razor 9 DOF IMU
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/

// Guard code to prevent multiple imports
#ifndef RAZORIMU_9DOF__H
#define  RAZORIMU_9DOF__H

// Main arduino code
#include "Arduino.h"
// Versatile for serial
#include "Stream.h"

// Axis values
#define PITCH 0
#define ROLL 1
#define YAW 2

// Serial method of connection
class RazorIMU_9DOF {
    // Raw values of Pitch, Roll and Yaw as received from the sensors
    float PRY_raw_values[3];
    float PRY_full_scale[3];   // 0 to 360 degree values
    float PRY_full_scale_ref[3];  // Reference values of Pitch, Roll and Yaw
    void Calculate_fullScales();
    // Initialize IMU - Initialize the reference values
    void GrabReference();
    // Update the raw values from the serial
    void GrabData();
    // Serial line to which the IMU is attached
    Stream *IMU_Serial;
public:
    // ##################   Constructors   ######################
    RazorIMU_9DOF();
    RazorIMU_9DOF(Stream *AttachedSerial);
    // ###############  Public member functions   ################
    // Attach IMU to serial
    void AttachIMUSerial(Stream *AttachedSerial);
    // Parse data from serial (raw) - Receive and store it
    void UpdateData();
    void ResetReference();   // Reset reference values to current values
    // #############   Retrieving data from object   ############
    // Retrieving raw PRY values
    float GetRaw_PITCH();
    float GetRaw_ROLL();
    float GetRaw_YAW();
    // Retrieving full scale RPY values
    float GetRoll();
    float GetPitch();
    float GetYaw();
};

// End of guard code
#endif
