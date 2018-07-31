# Introduction
This library is for defining any kind of base for a ground terrain robot.

**Note** : This library is still in developer beta, ask the developer before using

# Developers Guide
Here is the developers guide to the library

## Library Details

### Files in the library
Let's first explore about all the files in this library

#### BotBase.h
This is the header file and contains the class blueprint (prototype). We will explore the details about the class soon.

#### BotBase.cpp
This is the file that contains the main code for the class. In the header file, only the function prototypes are mentioned, the code for the functions (definition) are present in this file.

#### keywords.txt
This file contains the keywords that we want the Arduino IDE to identify. This provides syntax highlighting features for the library for convenience of the programmer.

#### README.md
The description file containing details about the library. The file that you are looking at right now

### Class contents
This library assumes the following :-
- You have a motor driver that requires only PWM and DIR (PWM and direction) signals to control the speed and direction of a motor.

Let's inspect in detail what all the members of the class do

#### Protected members
##### Variables

**<font color="#CD00FF">int</font> NUMBER_OF_WHEELS** : The number of motor powered wheels on the base of the bot.

**<font color="#CD00FF">int</font> \*PWM_pins** : The pin numbers which are connected to the PWM terminal of the motor driver. These tell the motor driver the amount of voltage to be given to the motors.

**<font color="#CD00FF">int</font> \*PWM_values** : The 8 bit (0 to 255) values of the PWM pin that specify the voltage on that pin. For example : If you're using a controller that operates on 5V logic level, then 0 signifies 0V, 127 signifies 2.4902V and 255 signifies 5V. In short N here specifies N * V/255 volts in real (where V is the logic level voltage).

**<font color="#CD00FF">int</font> \*DIR_pins** : The pin numbers which are connected to the DIR terminal of the motor driver. These tell the motor driver which direction to rotate the motor in (clockwise or counter clockwise).

**<font color="#CD00FF">int</font> \*DIR_values** : These are either HIGH or LOW. These are the directions of rotation for the motor. It's your wish to choose the directions (as per convenience).

**<font color="#CD00FF">String</font> name** : This is the name of the bot. This is used for debugging purposes and to avoid confusion in case of multiple instances. It's like an identity of the bot. It's suggested that you assign a unique name to every instance of this class.

**<font color="#FFB300">HardwareSerial</font> \*botDebuggerSerial** : This is the serial over which debugger messages are sent. It must be initialized beforehand (using the _Serial.begin_ function). It's also mentioned as _debugger serial_ at places.

**<font color="#CD00FF">int</font> debuggerPriorityLevel** : This variable is to signify the verbocity needed by the user while debugging. Messages having priority lesser that this will not be displayed on the _debugger serial_.

##### Member functions
**<font color="#CD00FF">void</font> <font color="#5052FF">setNumberOfWheelsTo</font>(<font color="#FF00FF">int</font> number)** : Sets the *NUMBER_OF_WHEELS* value to the passed *number*. It's a good idea to make a call to this in the constructor of the derived classes.

**<font color="#CD00FF">void</font> <font color="#5052FF">DebuggerOutput</font>(<font color="#FF00FF">int</font> Level, <font color="#FF00FF">String</font> output)** : Used to put a debugger message into the serial. All debugger messages have the following format :
<center>
$<font color="1FB000">name</font>$:L<font color="1FB000">level</font>: <font color="1FB000">output</font>
</center>
Where stuff in <font color="1FB000">green</font> is the *name* of bot, it's *debuggerPriorityLevel* and the *output* message passed to the function.

#### Public members
##### Constructors
Though you'll never create any memory for objects of this class, it's advised that you create a constructor anyways.

**<font color="#5052FF">BotBase</font>()** : Empty constructor

**<font color="#5052FF">BotBase</font>(<font color="#CD00FF">String</font> name, <font color="#FFB300">HardwareSerial</font> \*debugger_serial, <font color="#CD00FF">int</font> Level)** : 
