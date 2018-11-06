/* Example code to Test the PS2 Controller in Analog mode 
and use it to retrieve speed and angle from PS2 analog values*/

#include <PS2Controller.h>

PS2Controller myPS2(A11,A12);
void setup() {
  // put your setup code here, to run once:

Serial.begin(57600);

Serial.println("Going into loop ... ");
myPS2.InitializePS2Serial(115200);
//myPS2.InitializeDebugger(&Serial,0);
}

void loop() {

myPS2.ReadPS2Values();
myPS2.AdjustCoordinates();
myPS2.CalcAngleSpeed(1);
delay(40);
}
