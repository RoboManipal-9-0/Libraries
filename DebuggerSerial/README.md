# Introduction
This library is for defining and using a serial as a debugger.

**Node**: This library is still in developer beta, ask the developer before using.

Select guide : [Users Guide](users-guide) or [Developers Guide](developers-guide)

# Users Guide

## Downloading the library
It is suggested that you download the entire repository and then select this folder, so that you can enjoy the benefits of VCS like git. It makes it simpler to update the contents whenever patch fixes are done. You can simply open a terminal (or gitbash on windows), go to the folder where you want to save this repository and type the following command.
```bash
git clone https://github.com/RoboManipal-9-0/Libraries.git -b dev
```
_You might want to omit the `-b <branch>` tag if you're downloading from the master version_.

**<font color="#AA0000">Not recommended</font>** : You can download just this folder by clicking [here](placeholder).

## Using the library with Arduino
Move this folder into the arduino libraries folder on your PC. If you don't know where the libraries folder of your arduino is, you can check out the README file of this entire repository for this, click [here](../README.md).

## Examples
#### Repeated_HardwareSerial
**File**: Code [here](./examples/Repeated_HardwareSerial/Repeated_HardwareSerial.ino).
- Declare a DebuggerSerial and send messages of all priorities and a sensor reading every 5 seconds.

#### Repeated_SoftwareSerial_TX
**File**: Code [here](./examples/Repeated_SoftwareSerial_TX/Repeated_SoftwareSerial_TX.ino).
- Same as **Repeated_HardwareSerial** 
- We use a software serial instead of hardware serial here.

### Protocol implementation
- For `SENSOR_FEED` data
```
[%Timestamp%] $%Name%$ %Value%
```
- For `NOTIFICATION` data
```
[%Timestamp%] > %Message%
```
- For other priority levels
```
[%Timestamp% %LevelToString%] $%Name%$ %Message%
```
> **Timestamp** is the number of milliseconds passed after the initialization of the microcontroller.<br>
> **LevelToString** is the level converted to string form using the _PriorityLevelName_ function.<br>
> **Name**: Name of the debugger.<br>
> **Value**: Sensor floating point data converted to string type.<br>
> **Message**: String message to be sent.

# Developers Guide
Here is the developers guide to the library. <br>
This markdown is best viewed in [_Atom_](https://atom.io/) and [VSCode](https://code.visualstudio.com/) editor.

## Library Details

### Files in the library
Let's first explore about all the files in this library

#### DebuggerSerial.h
This is the header file and contains the class blueprint (prototypes). We will explore the details about the class soon.

#### DebuggerSerial.cpp
This is the file that contains the main code for the class. In the header file, only the function prototypes are mentioned, the code for the functions (definitions) are present in this file.

#### keywords.txt
This file contains the keywords that we want the Arduino IDE to identify. This provides syntax highlighting features for the library for convenience of the programmer.

#### README.md
The description file containing details about the library. The file that you are looking at right now

### Code description
This library assumes the following :-
- You have an ATMEGA Microcontroller (or a microcontroller supported by Arduino IDE) which will host the debugger on a _HardwareSerial_ or _SoftwareSerial_.

The purpose of the *DebuggerSerial* class is to create a pipeline for Debugger.

Let's explore the code in detail
### Debugger 
- Priority levels, each one of the is a constant defined in the file.
    - `SENSOR_FEED`: To send sensor data to the serial. Use _printSensorData_ to send sensor readings.
    - `NOTIFICATION`: To send out notifications from the library itself, it's suggested that the user doesn't use these. It's **only** for the library alone.
    - `DEBUG`: Debugging messages
    - `INFO`: Messages that given information messages
    - `WARNING`: Warning messages. An issue has occurred, but the functioning will not be affected.
    - `ERROR`: Error messages. An issue has occurred, the standard functioning might have been compromised.
    - `FATAL`: Fatal messages. An issue has occurred, the functioning is completely compromised.
- Global functions 
    -  **<font color="#5052FF">String</font> <font color="#f2e165">PriorityLevelName</font>(<font color="#76bef2">int</font> priorityLevel)**: Returns the _String_ equivalent of the priority level.

### DebuggerSerial class
#### Protected members
##### Variables
- **<font color="#87ff7c">Stream</font> \*debuggerSerial**: Main debugger serial through which the messages are transmitted.
- **<font color="#3d8aff">String</font> name**: Name of the debugger.
- **<font color="#3d8aff">int</font> debuggerPriorityLevel**: The priority level of debugger. Messages having a priority level lesser than this are going to be discarded.
- **<font color="#3d8aff">bool</font> debuggerEnabled**: Flag to check if the debugger is enabled or not.
- **<font color="#3d8aff">bool</font> debuggerSerialDefined**: Flag to check if the debugger serial has been attached or not.

##### Functions
- **<font color="#3d8aff">void</font> <font color="#f7e47b">DebuggerOutput</font>(<font color="#3d8aff">int</font> Level, <font color="#3d8aff">int</font> output)**: Print a message on the _debuggerSerial_.
- **<font color="#3d8aff">void</font> <font color="#f7e47b">RaiseNotification</font>(<font color="#3d8aff">String</font> message)**: Publish notifications about the _Debugger_ on the serial.

#### Public
##### Constructors
- **<font color="#fceb8f">DebuggerSerial</font> ()**: Empty constructor
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name)**: Assign name only
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">int</font> priorityLevel)**: Assign priority level only
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#87ff7c">Stream</font> \*debuggerSerial)**: Assign the debuggerSerial only
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name, <font color="#3d8aff">int</font> priorityLevel)**: Assign name and priority level to the debugger
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name, <font color="#87ff7c">Stream</font> \*debuggerSerial)**: Assign _name_ and _debuggerSerial_ to debugger
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name, <font color="#87ff7c">Stream</font> \*debuggerSerial, <font color="#3d8aff">int</font> priorityLevel)**: Assign _name_, _debuggerSerial_ and _priorityLevel_

##### Functions
- **<font color="#3d8aff">void</font> <font color="#f9e784">Initialize</font>(<font color="#3d8aff">String</font> name, <font color="#87ff7c">Stream</font> \*debuggerSerial, <font color="#3d8aff">int</font> priorityLevel)**: Initializer to assign _name_, _debuggerSerial_ and _priorityLevel_
- **<font color="#3d8aff">void</font> <font color="#f9e784">Initialize</font>(<font color="#87ff7c">Stream</font> \*debuggerSerial, <font color="#3d8aff">int</font> priorityLevel)**: Initializer for _debuggerSerial_ and _priorityLevel_
- **<font color="#3d8aff">void</font> <font color="#f9e784">AttachSerial</font>(<font color="#87ff7c">Stream</font> \*debuggerSerial)**: Attach the _debuggerSerial_ only (standalone)
- **<font color="#3d8aff">void</font> <font color="#f9e784">AttachSerial</font>(<font color="#3d8aff">String</font> name)**: Attach the _name_ only (standalone)
- **<font color="#3d8aff">void</font> <font color="#f9e784">SetDebuggerPriorityToLevel</font>(<font color="#3d8aff">int</font> minLevel)**: Attach the _debuggerPriorityLevel_ only (standalone)
- **<font color="#3d8aff">void</font> <font color="#f9e784">enableDebugger</font>()**: Enable the debugger
- **<font color="#3d8aff">void</font> <font color="#f9e784">disableDebugger</font>()**: Disable the debugger
- **<font color="#3d8aff">void</font> <font color="#f9e784">printMessage</font>(<font color="#3d8aff">int</font> level, <font color="#3d8aff">String</font> output)**: Print message to the _debuggerSerial_
- **<font color="#3d8aff">void</font> <font color="#f9e784">print</font>(<font color="#3d8aff">int</font> level, <font color="#3d8aff">String</font> output)**: Print message to the _debuggerSerial_ (alternate to printMessage)
- **<font color="#3d8aff">void</font> <font color="#f9e784">print</font>(<font color="#3d8aff">String</font> output, <font color="#3d8aff">int</font> level)**: Print message to the _debuggerSerial_ (alternate to printMessage). Arguments are reversed
- **<font color="#3d8aff">void</font> <font color="#f9e784">printSensorData</font>(<font color="#3d8aff">double</font> value)**: Print the value of a sensor reading on _debuggerSerial_.