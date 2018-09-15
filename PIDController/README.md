# Introduction
This library defines a PID controller ([wikipedia](https://en.wikipedia.org/wiki/PID_controller)).


~~**WARNING**: This library is still in development. Please ask the developers before using it.~~ <br>
Beta testing done :tada:

# User Guide
## Downloading the library
It is suggested that you download the entire repository and then select this folder, so that you can enjoy the benifits of VCS like git. It makes it simpler to update the contents whenever patch fixes are done. You can simply open a terminal (or gitbash on windows), go to the folder where you want to save this repository and type the following command.
```
git clone https://github.com/RoboManipal-9-0/Libraries.git -b Branch-AvneeshMishra
```
_You might want to omit the `-b <branch>` tag if you're downloading from the master branch_.

**Not recommended**: You can download _only_ this folder by clicking [here](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/RoboManipal-9-0/Libraries/tree/master/PIDController).

## Using the library with Arduino
Move this folder into the arduino libraries folder on your PC. If you don't know where the libraries folder of your arduino is, you can check out the README file of this entire repository for this, click [here](../README.md).<br>

# Developers Guide
Here is the developers guide to the library. <br>
This file is best viewed in the [_Atom_](https://atom.io/) text editor.

## Library Details
Here's a brief description of all the files in this library.

#### PIDController.h
This is the header file and contains the class blueprint (prototype). It contains the *PIDController* class. Details about the class is later in this documentation.

#### PIDController.cpp
This is the file that contains the main code for the class declared in *PIDController.h*.

#### keywords.txt
This file contains the keywords that we want the Arduino IDE to identify. This provides syntax highlighting features for the library for convenience of the programmer.

#### README.md
The description file containing details about the library. The file that you are looking at right now

### Class description
This library has the following classes
- PIDController
    - This class is the basic PID controller

**Class description for PIDController**
#### Private members
##### Variables
- **<font color="#CD00FF">double</font> Kp, Ki, Kd**: These are the PID parameters that can be adjusted for different dynamic and steady state responses.
- **<font color="#CD00FF">double</font> setPoint**: The target value that the control system has to achieve, as the steady state output.
- **<font color="#CD00FF">double</font> currentValue**: The current value of the control system which is achieved using a sensor feedback loop (passed through a transfer function). The current state value of the system, basically.
- **<font color="#CD00FF">double</font> previousValue**: The previous value of the system.
- **<font color="#CD00FF">double</font> currentErrorValue**: The current error value of the system. This is achieved by calculating `setPoint - currentValue` of the system. This is also called the _direct difference error_ of the system.
- **<font color="#CD00FF">double</font> previousErrorValue**: The previous value of the direct difference error. The `(currentErrorValue - previousErrorValue) * Kd` determines the dynamic characteristics of the system (damping on the system).
- **<font color="#CD00FF">double</font> accumulatedError**: The weighed sum of the current accumulated error and the current direct difference error. You can control the accumulation factor using the following variables. It's achieved by `accFactorPresent * currentErrorValue + accFactorPast * accumulatedError`. You can set the _accFactor_ values to better match your needs.
- **<font color="#CD00FF">double</font> accFactorPast, accFactorPresent**: The accumulation factors (as observed in the above equation) of the accumulated error values. These together with _Ki_ determine the steady state performance of the system.
- **<font color="#CD00FF">double</font> part_Kp, part_Kd, part_Ki**: The part of the error associated to proportionality, derivative and integral respectively. The error is calculated using `part_Kp +part_Kd + part_Ki` and received using the _retError_ function.
- **<font color="#CD00FF">String</font> name**: Name of the node, using which the debugger will publish messages on a serial (only Hardware Serials are supported for now).
- **<font color="#CD00FF">HardwareSerial</font> **\* **debuggerSerial**: Hardware Serial on which the debugger is attached. The messages are put on this serial.
- **<font color="#CD00FF">bool</font> debuggerAttached**: If false, the debugger doesn't print out messages. It's set to _true_ after debugger is Initialized using _InitializeDebugger_ function.
- **<font color="#CD00FF">int</font> debuggerPriorityLevel**: The user defined priority level of the debugger. Messages having a level lesser than _debuggerPriorityLevel_ aren't sent to the debugger.

##### Member functions
- **<font color="#CD00FF">void</font> <font color="#5052FF">DebuggerOutput</font>(<font color="#FF00FF">int</font> level, <font color="#FF00FF">String</font> message, <font color="#FF00FF">bool</font> printName = <font color="#FFB300">true</font>)**: Print a _message_ on the debugger. The message has a priority _level_ and anonimity can be maintained using the _printName_ flag. The message format is as follows
```
$%Name%$:L%level%: %message%
```
Where _%Name%_ is the name of the debugger (if printName is false, then it's PID\_CONTROLLER\_\_NAME), _%level%_ is the priority level (note that if this is less than _debuggerPriorityLevel_ then the message will not be displayed) and the _%message%_ is the message to print.
- **<font color="#CD00FF">void</font> <font color="#5052FF">calculateError</font>()**: Calculates the _previousErrorValue_, _currentErrorValue_ and _accumulatedError_ using the following three formulas.
```
previousErrorValue := currentErrorValue
currentErrorValue := setPoint - currentValue
accumulatedError := currentErrorValue * accFactorPresent + accumulatedError * accFactorPresent
```
- **<font color="#CD00FF">void</font> <font color="#5052FF">calculate_Kp_error</font>()**: Calculates the proportionality part of the error, which is `Kp * currentErrorValue`.
- **<font color="#CD00FF">void</font> <font color="#5052FF">calculate_Kd_error</font>()**: Calculates the differential part of the error, which is `Kd * (currentErrorValue - previousErrorValue)`.
- **<font color="#CD00FF">void</font> <font color="#5052FF">calculate_Ki_error</font>()**: Calculates the integral part of the error, which is `Ki * accumulatedError`.
- **<font color="#CD00FF">void</font> <font color="#5052FF">assignParameters</font>(<font color="#FF00FF">double</font> Kp, <font color="#FF00FF">double</font> Ki, <font color="#FF00FF">double</font> Kd)**: Assigns the values of Kp, Ki and Kd to the passed values.

#### Public Members
##### Constructors
- **<font color="#5052FF">PIDController</font>()**: Empty constructor of the class. It sets both the integral accumulation factors to 0.5 (their default value).
- **<font color="#5052FF">PIDController</font>(<font color="#FF00FF">String</font> name, <font color="#FF00FF">double</font> Kp, <font color="#FF00FF">double</font> Ki, <font color="#FF00FF">double</font> Kd)**: Initializes the name and assigns the control parameters of the controller.

##### Functions
- **<font color="#CD00FF">void</font> assignPIDParameters(<font color="#FF00FF">double</font> Kp, <font color="#FF00FF">double</font> Ki, <font color="#FF00FF">double</font> Kd)**: Assigns the PID parameters.
- **<font color="#CD00FF">void</font> assignSetPoint(<font color="#FF00FF">double</font> setPointValue)**: Assigns the set point value (target value) for the controller to achieve.
- **<font color="#CD00FF">void</font> setAccFactor(<font color="#FF00FF">double</font> newValuePast, <font color="#FF00FF">double</font> newValuePresent)**: Sets the value of _accFactorPast_ to _newValuePast_ and _accFactorPresent_ to _newValuePresent_. Adjusts the updation parameters of integral error (accumulatedError) part.
- **<font color="#CD00FF">void</font> assignCurrentValue(<font color="#FF00FF">double</font> currentValue)**: Assigns the _currentValue_ to the controller.
- **<font color="#CD00FF">double</font> retError()**: Returns the error value calculated using `part_Kp +part_Kd + part_Ki`.
- **<font color="#CD00FF">double</font> retError(<font color="#FF00FF">double</font> currentValue)**: Assigns the current value and then returns the error.
- **<font color="#CD00FF">double</font> retError(<font color="#FF00FF">double</font> setPoint, <font color="#FF00FF">double</font> currentValue)**: Assigns the _setPoint_ and _currentValue_ and then returns the error.
- **<font color="#CD00FF">double</font> getCorrectedValue()**: It calculates the error (using the _retError_ function) and returns `error + currentValue`. This is called the _correctedValue_.
- **<font color="#CD00FF">double</font> getCorrectedValue(<font color="#FF00FF">double</font> currentValue)**: Sets the _currentValue_ and then returns the _correctedValue_.
- **<font color="#CD00FF">double</font> getCorrectedValue(<font color="#FF00FF">double</font> setPoint, <font color="#FF00FF">double</font> currentValue)**: Sets the _setPoint_ and _currentValue_, then returns the _correctedValue_.
- **<font color="#CD00FF">void</font> attachName(<font color="#FF00FF">String</font> name)**: Assigns a _name_ to the controller.
- **<font color="#CD00FF">void</font> InitializeDebugger(<font color="#FF00FF">HardwareSerial</font> **\* ** debuggerSerial, <font color="#FF00FF">int</font> priorityLevel)**: Initializes the debugger on _debuggerSerial_ (for now only hardware serials are supported). It also sets the _debuggerPriorityLevel_ to _priorityLevel_.
- **<font color="#CD00FF">void</font> InitializeDebugger(<font color="#FF00FF">String</font> name, <font color="#FF00FF">HardwareSerial</font> **\* ** debuggerSerial, <font color="#FF00FF">int</font> priorityLevel)**: Assigns _name_, initializes the debugger on _debuggerSerial_ (for now only hardware serials are supported). It also sets the _debuggerPriorityLevel_ to _priorityLevel_.
