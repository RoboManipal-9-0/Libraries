# Introduction
This library is to actuate a Servo chain consisting of any number of Dynamixels and Pololus in any order.

# User's Guide
## Circuit diagrams :
Please refer to the images below for pinouts and connections: 
![Dynamixel in Daisy Chain](../Images/ax12chain.png)
## Downloading the Library
It's suggested that you download the entire repository and then select the folder ServoChain. You can simply open a terminal (or gitbash on windows), go to the folder where you want to save this repository and type the following command.
```
git clone https://github.com/RoboManipal-9-0/Libraries.git -b Branch-Akshatha
``` 
This library depends on the following libraries that you'll need to download and add to your Arduino libraries folder: 

- [DynamixelSerialX library](https://sourceforge.net/projects/dynamixelforarduino/files/?source=navbar)
{ X here stands for the Serial that you will be using to connect the Dynamixel chain to }

- [XYZrobotServo](https://github.com/pololu/xyzrobot-servo-arduino)

## Using the library with Arduino
Move this folder into the arduino libraries folder on your PC. 

## Library Details

### Files in the Library
The files in the library are :

#### ServoChain.h
This is the header file and contains the class blueprint (prototype). We will explore the details about the class soon.

#### ServoChain.cpp
This file contains the main code inclusing the function definitions.

#### README.md
The description files containing details about the library.

###  Class Description
This library assumes the following:-
- You have a Half Duplex to Full Duplex convertor that enables the interfacing of Dynamixels with Arduino.
- The Dynamixels and Pololus are connected in daisy chain to the respective Serials.
**Note** : The DynamixelLibrary version that you download must be consistent with the Serial you connect it to.

Let's inspect in detail what all the members of the class do
#### Protected Members
#### Variables
###### Servo variables for the chain :
- **<font color="#CD00FF">int</font> \*positions** : This contains the positions of the servos on a scale of 0-1023.

- **<font color="#CD00FF">int</font> \*servo_IDs** : These are the Servo IDs of the Dynamixels and Pololus ( the Servo IDs range from a value of 0-255 ,where 254 stands for the Broadcast ID)

- **<font color="#CD00FF">int</font> \*select**    : The select value indicates if the servo at the joint is a Dynamixel (1) or a Pololu (0)

- **<font color="#CD00FF">int</font> CHAIN_LENGTH**: The number of smart servos in the Servo Chain

###### Debugger: 
- **<font color="#FFB300">HardwareSerial</font> \*servoDebuggerSerial** : This is the serial over which debugger messages are sent. It must be initialized beforehand (using the _Serial.begin_ function). 

- **<font color="#CD00FF">int</font> debuggerPriorityLevel** : This variable is to signify the verbocity needed by the user while debugging. Messages having priority lesser that this will not be displayed on the _debugger serial_.

###### Dynamixel :
- **<font color="#CD00FF">int</font> NUMBER_OF_DYNAMIXELS**: The number of dynamixels in the servo chain

- **<font color="#CD00FF">int</font> selection_pin**: To set the direction pin for Dynamixels.

- **<font color="#CD00FF">int</font> dynamixel_speeds**: To set the speed at which the Dynamixels move.

- **<font color="#FFB300">HardwareSerial</font> \*dynamixelSerial** : The Serial that the Dynamixels in the chain are attached to. This should be in agreement with the Dynamixel Library included.

###### Pololu:

- **<font color="#CD00FF">int</font> NUMBER_OF_POLOLUS**: The number of pololus in the servo chain

- **<font color="#CD00FF">int</font> pullup_pin**: The pullup pin the Pololus are attached to.

- **<font color="#CD00FF">int</font> pololu_playtimes**: The desired time taken for the Pololu movement.  

- **<font color="#FFB300">HardwareSerial</font> \*pololuSerial** : The Serial that the Pololus in the chain are attached to. This should be in agreement with the Dynamixel Library included.

##### Member functions

- **<font color="#CD00FF">void</font> <font color="#5052FF">DebuggerOutput</font>(<font color="#FF00FF">int</font> Level, <font color="#FF00FF">String</font> output)** : Used to put a debugger message into the serial. All debugger messages have the following format :<br>
```
$:L%level%: %output%
```
Where stuff in % is *debuggerPriorityLevel* and the *output* message passed to the function respectively.


#### Public Members
##### Constructors
- **<font color="#5052FF">ServoChain</font>()**: The empty constructor for the class.
