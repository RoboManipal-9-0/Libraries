/*
	RhinoSerial - Sample Code for Serial Communication for Rhino RMCS-220X 
	Copyright (c) 2018 RoboManipal. All right reserved
	File created by : Shashank Goyal
	Test Status: Pending.
*/

#include <RhinoServo.h>

#define RhinoSerial Serial3

RhinoServo R = RhinoServo(SERIAL);

void setup()
{
	// Begin Serial Communication at 9600 baudrate.
	Serial.begin(9600);
	// Begin RhinoSerial Communication at 9600 baudrate.
	RhinoSerial.begin(9600);
	// Attach Serial Line to the Rhino.
	R.AttachRhino_Serial(&RhinoSerial);
	// Enable Debugger for Rhino 1.
	R.debugger.Initialize("Rhino", &Serial, DEBUG);

	// Uncomment the following to Disable Debugger -
	// R.debugger.disableDebugger();
}

void loop()
{
	while (Serial.available())
	{
		switch (Serial.read())
		{
			case 'M':	// Move to Position
			R.Moveto(Serial.parseInt());
			break;

			///////////////////////////////////////////////////////////

			case 'm':	// Move Relative to Current Position
			R.MovetoRel(DEGtoCOUNT(Serial.parseInt()));
			break;

			///////////////////////////////////////////////////////////

			case 'R':	// Reset Encoder Value
			R.Reset_Reference(Serial.parseInt());
			break;

			///////////////////////////////////////////////////////////

			case 'r':	// Reset Encoder Value to Zero
			R.Reset_Reference();
			break;

			///////////////////////////////////////////////////////////

			case 'P':	// Read Position
			Serial.println(R.GetCurrent_Position());
			break;

			///////////////////////////////////////////////////////////

			case 'A' : 	// Get I2C Address 
			R.GetI2C_Address();
			break;

			///////////////////////////////////////////////////////////

			case 'S':	// Set I2C Address
			R.SetI2C_Address(Serial.parseInt());
			break;

			///////////////////////////////////////////////////////////			

			case 'W': // Set Constant Rotation of the Motor 
			R.Set_Dir_Speed(Serial.parseInt());
			break;
		}
	}
}
