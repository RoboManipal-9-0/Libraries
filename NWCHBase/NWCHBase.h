/*
    NWCHBase.h - Library for N wheel concentric holonomic base made using omni wheels
    Copyright (c) 2018 RoboManipal. All right reserved
    File created by : Avneesh Mishra
    Last commit done by : Avneesh Mishra
*/
// Sanity check
#ifndef NWCHBASE_H
#define NWCHBASE_H

// Arduino main files
#include "Arduino.h"
#include "BotBase.h"

class NWCHBase : public BotBase {
protected:
    float *angles;      // Array of angle (in radians) values 
    // Main motion code
    void Move_PWM_Angle(int PWM, float angle_radian, float w = 0);
public:
    // Constructors
    NWCHBase();
    NWCHBase(int num_wheels);
    NWCHBase(int num_wheels, int *angles_deg);
    // Initializer functions
    void InitializeWheels(int num_wheels);
    void InitializeWheels(int *angles_deg);
    void InitializeWheels(int num_wheels, int *angles_deg);
};

#endif
