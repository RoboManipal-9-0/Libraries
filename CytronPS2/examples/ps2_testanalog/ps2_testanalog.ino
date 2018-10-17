/*
This example shows how to read a joystick value on PS2 Controller.

Function:
  readButton(button); 
                      // Analog button: return a value

  Analog button:
    PS2_JOYSTICK_LEFT_X_AXIS
    PS2_JOYSTICK_LEFT_Y_AXIS
    PS2_JOYSTICK_RIGHT_X_AXIS
    PS2_JOYSTICK_RIGHT_Y_AXIS
    PS2_JOYSTICK_LEFT_UP
    PS2_JOYSTICK_LEFT_DOWN
    PS2_JOYSTICK_LEFT_LEFT
    PS2_JOYSTICK_LEFT_RIGHT
    PS2_JOYSTICK_RIGHT_UP
    PS2_JOYSTICK_RIGHT_DOWN
    PS2_JOYSTICK_RIGHT_LEFT
    PS2_JOYSTICK_RIGHT_RIGHT


*/

#include <SoftwareSerial.h>
#include <CytronPS2.h>

CytronPS2 ps2;
//Cytron_PS2Shield ps2; // HardwareSerial, note: 

void setup()
{
   // SoftwareSerial: Rx and Tx pin
  ps2.Initialize(8,9);
  ps2.begin(115200); // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(57600); // Set monitor baudrate to 9600
}

void loop()
{
  // Open monitor and move left joystick in x axis
  // Analog value will be displayed
  Serial.println(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS));
  delay(50);
}
