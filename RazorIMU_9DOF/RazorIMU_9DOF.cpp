/*
  RazorIMU_9DOF.h - Library to deal with Razor 9 DOF IMU
  Copyright (c) 2018 RoboManipal. All right reserved
  File created by : Avneesh Mishra
  Last commit done by : Avneesh Mishra
*/
// Include library
#include "RazorIMU_9DOF.h"

// ################### Constructors #######################
RazorIMU_9DOF::RazorIMU_9DOF() {
    // Empty constructor
}
RazorIMU_9DOF::RazorIMU_9DOF(Stream *AttachedSerial) {
    // Connect IMU Serial
    this->AttachIMUSerial(AttachedSerial);
}

// ############# Member Functions #########################
// Attach Serial
void RazorIMU_9DOF::AttachIMUSerial(Stream *AttachedSerial) {
    // Connect IMU Serial
    this->IMU_Serial = AttachedSerial;
    // Debugger message (level: INFO)
    // IMU Serial attached
    this->debugger.print("IMU Serial attached", INFO);
}

// Get raw data from the serial
void RazorIMU_9DOF::GrabData() {
    // Send out a '#f' on the serial
    this->IMU_Serial->println("#f");
    // Debugger message about the inquiry
    this->debugger.print("Sending a '#f' to IMU serial", DEBUG); 
    // Wait until response
    while(!this->IMU_Serial->available()) {
        // Do nothing
    }
    // Debugger message (Level: DEBUG)
    // Y: %YAW% P: %PITCH% R: %ROLL%
    // For example:
    // Y: -172 P: 96 R: 100
    String msg = "Y: ";
    this->IMU_Serial->readStringUntil('=');   // Waste the '#YPR=' part
    this->RPY_raw_values[YAW] = this->IMU_Serial->readStringUntil(',').toFloat();
    msg.concat(this->RPY_raw_values[YAW]);
    msg.concat(" P: ");
    this->RPY_raw_values[PITCH] = this->IMU_Serial->readStringUntil(',').toFloat();
    msg.concat(this->RPY_raw_values[PITCH]);
    msg.concat(" R: ");
    this->RPY_raw_values[ROLL] = this->IMU_Serial->readStringUntil('\n').toFloat();
    msg.concat(this->RPY_raw_values[ROLL]);
    // Reading done
    this->debugger.print(msg, DEBUG);
    /*
    // /////  Dead code..... Needs fixing (temporary patch added)   ////////////
    // Output is like : #YPR=<YAW>,<PITCH>,<ROLL>
    // In case the IMU side has been modified to send in another order
    if (this->IMU_Serial->available()) {
        this->IMU_Serial->read(); // Read the '#' in the beginning
        // Get the order of 'Y', 'P' and 'R' as strings
        String s1 = this->IMU_Serial->readStringUntil('=');
        for (int i = 0; i < s1.length(); i++) {
            String s_buffer = this->IMU_Serial->readStringUntil(',');
            int c;   // Command sent
            if (s1[i] == 'Y') {
                msg.concat(" Y: ");
                c = YAW;
            } else if (s1[i] == 'P') {
                msg.concat(" P: ");
                c = PITCH;
            } else if (s1[i] == 'R') {
                msg.concat(" R: ");
                c = ROLL;
            }
            // Assign the PITCH, ROLL and YAW values
            this->RPY_raw_values[c] = s_buffer.toFloat();
            msg.concat(this->RPY_raw_values[c]);
        }
    }
    */
}

// Convert raw data to full scale: 0 to 360 degree data
void RazorIMU_9DOF::Calculate_fullScales() {
    // Debugger message (Level: DEBUG)
    // Full scale RPY values: %FS_PITCH% %FS_ROLL% %FS_YAW%
    String msg = "Full scale RPY values: ";
    for (int i = 0; i < 3; i++) {
        /*
        *    If raw > 0 => 0 to 180, then let it be as it is
        *    else if raw < 0 => -180 to -0, then it must be converted to
        *       full scale by adding 360 to the negative value
        *       Basically, it's 360 - |raw|, but since raw is already negative
        *       we can do 360 + raw.
        */
        if (this->RPY_raw_values[i] >= 0) {
            this->RPY_full_scale[i] = this->RPY_raw_values[i];
        } else {
            this->RPY_full_scale[i] = 360 + this->RPY_raw_values[i];
        }
        msg.concat(this->RPY_full_scale[i]);
        msg.concat(" ");
    }
    this->debugger.print(DEBUG, msg);
}

// Update all the RPY parameters
void RazorIMU_9DOF::UpdateData() {
    // Grab the data from GrabData function
    this->GrabData();
    // Update the full scale values
    this->Calculate_fullScales();
}

// Get reference values for full scale values
void RazorIMU_9DOF::GrabReference() {
    // Reset the reference values
    this->UpdateData();
    // Debugger message (Level: INFO)
    // RPY reference set to: %PITCH_REF% %ROLL_REF% %YAW_REF%
    // For example:
    // RPY reference set to: 187 90 86
    String msg = "RPY reference set to: ";
    for (int i = 0; i < 3; i++) {
        this->RPY_full_scale_ref[i] = RPY_full_scale[i];
        msg.concat(this->RPY_full_scale_ref[i]);
        msg.concat(" ");
    }
    this->debugger.print(msg, INFO);
}
// Get new reference
void RazorIMU_9DOF::ResetReference() {
    this->GrabReference();    // Get new reference
}
// -------- Getting raw RPY values from IMU ----------
float RazorIMU_9DOF::GetRaw_PITCH() {
    // Read Pitch
    return this->RPY_raw_values[PITCH];
}
float RazorIMU_9DOF::GetRaw_ROLL() {
    // Read Roll
    return this->RPY_raw_values[ROLL];
}
float RazorIMU_9DOF::GetRaw_YAW() {
    // Read Yaw
    return this->RPY_raw_values[YAW];
}
// Getting the full scale values
float RazorIMU_9DOF::GetPitch() {
    // Pitch
    return this->RPY_full_scale[PITCH];
}
float RazorIMU_9DOF::GetRoll() {
    // Roll
    return this->RPY_full_scale[ROLL];
}
float RazorIMU_9DOF::GetYaw() {
    // Yaw
    return this->RPY_full_scale[YAW];
}
// Getting relative values
float RazorIMU_9DOF::GetRel_YAW() {
    // Yaw difference from the reference
    return this->RPY_full_scale[YAW] - this->RPY_full_scale_ref[YAW];
}
float RazorIMU_9DOF::GetRel_PITCH() {
    // Pitch difference from the reference
    return this->RPY_full_scale[PITCH] - this->RPY_full_scale_ref[PITCH];
}
float RazorIMU_9DOF::GetRel_ROLL() {
    // Roll difference from the reference
    return this->RPY_full_scale[ROLL] - this->RPY_full_scale_ref[ROLL];
}
