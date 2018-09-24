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
    float PRY_raw_values[3];
    Stream *IMU_Serial;

};

// End of guard code
#endif
