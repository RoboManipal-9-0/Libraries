# Introduction
This library helps interface a PS2 Controller with Arduino and calculate normalised paramters such as the angle
and speed of the bot motion. This class uses the modified Cytron PS2 Shield library.

# User's Guide
## Conventions
Please refer to the image below for the conventions followed in the library.
![Joystick conventions](../DATA/Images/JoystickConventions.png)
The image is taken from top view.
- The same convention is followed for both the joystick values, i,e right and left.
- The *zero axis* is shown in red. The cartesian coordinate frame is as marked in the figure.
- The maximum values of the speed of motion are recorded along the circumference of the circle.

## Downloading the Library
It's suggested that you download the entire repository and then select the folders `PS2Controller` and `CytronPS2` (in case you haven't already imported it). This library depends upon the **CytronPS2** library

## Using the library with Arduino
Move the folders into the *arduino libraries* folder on your PC.

## Examples
After moving the library to the correct location, you can check the following examples.

The first two examples are to give you a basic introduction to the CytronPS2 library
### Example 
The example we're looking for is here 
### Example 2
### Example 3

# Developers guide

## Library Details
### Files in the Library
The files in the library are :

#### PS2Controller.h
This is the header file and contains the class blueprint (prototype). We will explore the details about the class soon.

#### PS2Controller.cpp
This is the file that contains the main code for the class. In the header file, only the function prototypes are mentioned, the code for the functions (definition) are present in this file.

#### README.md
The description file containing details about the library. The file that you at right now.
###  Class Description
#### Protected Members
#### Variables
##### Member functions

#### Public Members
##### Constructors
##### Member Functions

### Additional References
EduBot Cytron Tutorial with PS2 Shield : - [Cytron-PS2-Shield Tutorial](https://tutorial.cytron.io/2015/07/23/using-cytron-ps2-shield-with-arduino-edubot-2/)
Original Cytron PS2 Shield library : [Cytron-PS2-Shield](https://github.com/CytronTechnologies/Cytron_PS2Shield)
