#include<NWCHBase.h> // Include the library

int no_wheels = 4;    // 4 wheel drive
// Wheels are at the following angles
int angles_degrees[] = {45, 135, 225, 315};   
// Pins connected to the motor drivers
int PWM_pins[] = {7,8,9,10};          // List of PWM pins
int DIR_pins[] = {50, 51, 52, 53};    // List of DIR pins
// Reverse connection list
/*
 * Forward connected : If HIGH is gven, axis of rotation is positive
 * Backward connected : If LOW is gven, axis of rotation is positive
 *  1st motor is reverse connected
 *  2nd motor is forward connected
 *  3rd motor is reverse connected
 *  4th motor is forward connected
 */
bool reverseDIRs[] = {true, false, true, false};

// Class object (an object of class NWCHBase)
NWCHBase FourWheelBase;
void setup() {
  Serial.begin(115200);  // Setup the serial for the debugger
  // Intialize the debugger of the Base, name: "FWBase", serial passed
  FourWheelBase.debugger.Initialize("FWBase", &Serial);
  FourWheelBase.InitializeWheels(no_wheels, angles_degrees);   // Initialize wheels (used functon because it prints onto debugger)
  FourWheelBase.AttachPins(PWM_pins, DIR_pins, reverseDIRs);   // Attach pins for the motor driver
}

void loop() {
  // Move the bot at 0 degrees (forward) with speed 100. Value vector comes out to be (70, -70, -70, 70)
  FourWheelBase.Move(100, 0);     // Move function
}
