# Introduction
The **FourSBase** library is to control a four wheel holonomic drive for omni wheels. This class is derived from [BotBase](../BotBase/) class, so it's suggested that you go through it's documentation first.<br>

# Index
- [Introduction](#introduction)
- [Index](#index)
    - [Information](#information)
        - [Testing](#testing)
    - [Conventions](#conventions)
- [Users Guide](#users-guide)
    - [Downloading the Library](#downloading-the-library)
    - [Using the library with Arduino](#using-the-library-with-arduino)
    - [Using the library](#using-the-library)
    - [Examples](#examples)
        - [~~Example 1~~ (Example outdated)](#example-1-example-outdated)
- [Developers Guide](#developers-guide)
    - [Library Details](#library-details)
        - [Files in the library](#files-in-the-library)
            - [FourSBase.h](#foursbaseh)
            - [FourSBase.cpp](#foursbasecpp)
            - [keywords.txt](#keywordstxt)
            - [README.md](#readmemd)
        - [Class description](#class-description)
            - [Protected members](#protected-members)
                - [Variables](#variables)
                - [Mamber functions](#mamber-functions)
            - [Public members](#public-members)
                - [Constructors](#constructors)
                - [Member Functions](#member-functions)
- [Debugger notifications](#debugger-notifications)
    - [Debug level](#debug-level)

## Information
### Testing
This library has been tested on the wheel configuration shown below
![FourSBase image](../.DATA/Images/FourSBase_Wheels.png)
The image above is taken from the top view.
## Conventions
Please refer to the image below for the conventions used in this library
![FourSBase conventions](../.DATA/Images/FourSBase_WheelConfigurations.png)
The image above is taken from the top view.
- The *wheels* are numbered in a counter clockwise sence from 1 to 4.
- The *axis of rotation* is shown in light blue axis lines.
- The *sence of rotation* that is considered positive is shown by golden arrows for each wheel. Note that the axis of rotation is decided using the right hand rule.
    - For instance, the first wheel (top right) rotates in such a way that it's top point moves towards left and the bottom point moves towards right as seen from top view. Only then the rotation on the wheel is considered positive, else it's negative.
- The *zero axis* (the axis considered at 0<sup>o</sup>) is shown in red. The +ve sence of rotational measurement is shown in light red.

# Users Guide

## Downloading the Library
It's suggested that you download the entire repository and then select the folders `FourSBase` and `BotBase` (in case you haven't already imported it). This library depends upon the **BotBase** library (link [here](../BotBase/)).

## Using the library with Arduino
Move the folders into the *arduino libraries* folder on your PC. If you don't know where the libraries folder of your arduino installation is, you can check out the README file of this entire repository (click [here](../README.md)).

## Using the library
- Include the header file in the program.
- Create arrays for the PWM pins, DIR pins and reverse directions (if needed). Check the [BotBase documentation](./../BotBase/) for more.
- Create an object of the **FourSBase** class.
- Call the _AttachPins_ function (it's there in [BotBase documentation](./../BotBase/)). Pass it the PWM pins, DIR pins and reverseDIR values.
- Call the **Move** function to apply motion to the bot. (The description about this is in the [BotBase documentation](./../BotBase/))

## Examples
After moving the library to the correct location, you can check the following examples.
### ~~Example 1~~ (Example outdated)
You can check the **Competitions** repository (link [here](https://github.com/RoboManipal-9-0/Competitions)) for this example. The example we're looking for is [here](https://github.com/RoboManipal-9-0/Competitions/tree/master/WRO2018/Senior_Team/Testing_Codes/FourSBase_Test1) (WRO2018/Senior_Team/Testing_Codes/FourSBase_Test1). You can download it by clicking [here](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/RoboManipal-9-0/Competitions/tree/master/WRO2018/Senior_Team/Testing_Codes/FourSBase_Test1) and extracting the folder. The code inside the *.ino* file must look something like what's shown below
![FourSBase example code](../.DATA/Images/FourSBase_Code.png)<br>
Before we get started with the example walkthrough, let's start with assumptions
- You are using motor drivers that require only two control inputs, PWM (PWM voltage) and DIR (Direction, 1 is +ve sence rotation and 0 is -ve sence rotation).
- Wheels are connected in the following manner to the microcontroller (Arduino Mega in our example).<br>

| Wheel number | PWM Pin | Direction pin | Direction Connection Reversed<sup>\*</sup> |
| :---------: | :-------: | :---------: | :-----------: |
| 1  | 10 | 53 | Yes |
| 2  |  7 | 49 | No  |
| 3  |  8 | 47 | No  |
| 4  |  9 | 51 | No  |

<sup>\*</sup> *Direction connection reversed*: When you give 1 to DIR pin of that particular motor, it rotates in the -ve sence instead of the +ve sence. You can simply set up a boolean array as shown in code to handle this problem, no need of changing electrical connections.<br>
*You can have different connections as well, these are just for this example.*

- Simply, upload this code to Arduino Mega, make the connections as mentioned in the table and then you're ready to give serial commands to move the bot.
- To move the bot at some magntude (a measure of speed) (say 60) and at an angle (say 45<sup>o</sup>), give it the following command:
```bash
P60A45
```
You can even give it in individual pieces as well (or even have spaces), `P60` sets the PWM to 60 and `A45` sets the angle of motion to 45<sup>o</sup>. Note the positive sence of rotational measurement from conventions section. For now, the control commands are as follows<br>

| Command | Arguments | Comments |
| ------- | --------- | -------- |
|P   | VAL_LEN  | Set the length of the motion vector (-ve values are allowed) |
|A   | VAL_ANG_DEG  | Sets the angle (in degrees) of the motion vector (-ve values are allowed) |

# Developers Guide
You're suggested to go through the **BotBase** documentation first, link [here](../BotBase/).<br>
## Library Details
### Files in the library
Let's first explore about all the files in this library

#### FourSBase.h
This is the header file and contains the class blueprint (prototype). We will explore the details about the class soon.

#### FourSBase.cpp
This is the file that contains the main code for the class. In the header file, only the function prototypes are mentioned, the code for the functions (definition) are present in this file.

#### keywords.txt
This file contains the keywords that we want the Arduino IDE to identify. This provides syntax highlighting features for the library for convenience of the programmer.

#### README.md
The description file containing details about the library. The file that you are looking at right now

### Class description
This library assumes the following :-
- You have a motor driver that requires only PWM and DIR (PWM and direction) signals to control the speed and direction of a motor.

This class is derived directly from the BotBase class (public inheritance).

#### Protected members
##### Variables
- **<font color="#CD00FF">int</font> \* reverseDIRs**: An array of boolean values (one per wheel). If true, then the direction values will be reversed (check the convention from the diagram).

##### Mamber functions
- **<font color="#CD00FF">void</font> <font color="#5052FF">Move_PWM_Angle</font>(<font color="#FF00FF">int</font> PWM, <font color="#FF00FF">float</font> angle_radians)**: Function responsible for motion of the bot. The library sets the *PWM_values* and *DIR_values* from the *PWM* and *angle_radians* passed. It also calls the *MoveMotor* function from the BotBase library.

#### Public members
##### Constructors
- **<font color="#5052FF">FourSBase</font>()**: The empty constructor for the class.

##### Member Functions
- **<font color="#CD00FF">void</font> <font color="#5052FF">AddPins</font>(<font color="#FF00FF">int</font> \*PWM\_pins, <font color="#FF00FF">int</font> \*DIR\_PINs, <font color="#FF00FF">bool</font> \*reverseDIRs)**: Attaches the *PWM\_pins*, *DIR\_PINs* and *reverseDIRs* to the bot base.

# Debugger notifications
## Debug level
1. **Move_PWM_Angle** functions<br>
    Prints the wheel vectors.
    ```
    [%TIMESTAMP% DEBUG] $%name%$ Calculated wheel vectors : [ %val1% %val2% %val3% %val4% ]
    ```
    For example:
    - After 18000 milliseconds, `FSB01` (name) develops vectors `[ 100 0 -100 0 ]`.
        ```
        [18000 DEBUG] $FSB01$ Calculated wheel vectors : [ 100 0 -100 0 ]
        ```


[![Image](https://img.shields.io/badge/Developer-TheProjectsGuy-blue.svg)](https://github.com/TheProjectsGuy)
