/*
This example shows how to retrieve a button status on PS2 Controller.

Function:
  readButton(button); // Read button status, it will return corresponding data
                      // Digital button: 0 = pressed, 1 = released
                      // Analog button: return a value

  Digital button:
    PS2_SELECT
    PS2_JOYSTICK_LEFT
    PS2_JOYSTICK_RIGHT
    PS2_START
    PS2_UP
    PS2_RIGHT
    PS2_DOWN
    PS2_LEFT
    PS2_LEFT_2
    PS2_RIGHT_2
    PS2_LEFT_1
    PS2_RIGHT_1
    PS2_TRIANGLE
    PS2_CIRCLE
    PS2_CROSS
    PS2_SQUARE

  
*/

#include <SoftwareSerial.h>
#include <CytronPS2.h>

CytronPS2 ps2; 
// SoftwareSerial: Rx and Tx pin
//Cytron_PS2Shield ps2; // HardwareSerial

#define LEDPIN  13

void setup()
{
  ps2.Initialize(8,9);
  ps2.begin(115200); // This baudrate must same with the jumper setting at PS2 shield

  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
}

void loop()
{
  // LED on main board will light up if 'Select' button is pressed
  if(ps2.readButton(PS2_SELECT) == 0) // 0 = pressed, 1 = released
  {
    digitalWrite(LEDPIN, HIGH);
  }
  else
  {
    digitalWrite(LEDPIN, LOW);
  }
}
