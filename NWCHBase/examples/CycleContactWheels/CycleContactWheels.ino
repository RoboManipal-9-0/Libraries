/*
 * MWCHBase example
 * 
 * Created by: Avneesh Mishra
 * Maintained by: Avneesh Mishra
 * 
 */
// Include library
#include<NWCHBase.h>

// Starting configuration
int no_wheels = 4;
// Angle configuratiom
int angles_degrees[] = {45, 135, 225, 315};

// PWM and DIR pins connected to the motor driver
int PWM_pins[] = {7,8,9,10};
int DIR_pins[] = {50, 51, 52, 53};
// Reverse connection array
bool reverseDIRs[] = {true  , false, true, false};

// Main object
NWCHBase FourWheelBase;
void setup() {
  // Serial for debugger
  Serial.begin(115200);
  // Setup debugger
  FourWheelBase.debugger.Initialize("FWBase", &Serial, 0);
  FourWheelBase.InitializeWheels(no_wheels, angles_degrees);   // Initialize configuration
  FourWheelBase.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Initialize pins
}
int currConfNo = 1;  // Current configuration
void loop() { 
  FourWheelBase.Move(100, 0);   // Move forward (0 degrees) with 100 PWM
  if (millis() > 5000 && currConfNo < 2) {
    // Change to second configuration
    currConfNo = 2;
    angles_degrees[0] = 0;
    angles_degrees[1] = 90;
    angles_degrees[2] = 180;
    angles_degrees[3] = 270;
  } else if (millis() > 10000 && currConfNo < 3) {
    // Change to third configuration
    currConfNo = 3;
    angles_degrees[0] = 90;
    angles_degrees[1] = 210;
    angles_degrees[2] = -30;
    FourWheelBase.InitializeWheels(3);  // 3 wheels only
  } else if (millis() > 15000 && currConfNo < 4) {
    // Change to fourth configuration
    currConfNo = 4;
    angles_degrees[0] = 0;
    angles_degrees[1] = 180;
    FourWheelBase.InitializeWheels(2);  // 2 wheels
  } else if (millis() > 20000 && currConfNo < 5) {
    //// Change back to first configuration
    currConfNo = 5;
    angles_degrees[0] = 45;
    angles_degrees[1] = 135;
    angles_degrees[2] = 225;
    angles_degrees[3] = 315;
    FourWheelBase.InitializeWheels(4);  // Back to 4 wheels
  }
}
