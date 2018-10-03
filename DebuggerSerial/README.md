# Introduction
This library is for defining and using a serial as a debugger.

**Node**: This library is still in developer beta, ask the developer before using.

Select guide : [Users Guide](users-guide) or [Developers Guide](developers-guide)

# Users Guide

## Downloading the library
It is suggested that you download the entire repository and then select this folder, so that you can enjoy the benifits of VCS like git. It makes it simpler to update the contents whenever patch fixes are done. You can simply open a terminal (or gitbash on windows), go to the folder where you want to save this repository and type the following command.
```bash
git clone https://github.com/RoboManipal-9-0/Libraries.git -b dev
```
_You might want to omit the `-b <branch>` tag if you're downloading from the master version_.

**<font color="#AA0000">Not recommended</font>** : You can download just this folder by clicking [here](placeholder).

## Using the library with Arduino
Move this folder into the arduino libraries folder on your PC. If you don't know where the libraries folder of your arduino is, you can check out the README file of this entire repository for this, click [here](../README.md).

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

### Class description
This library assumes the following :-
- You have an ATMEGA Microcontroller (or a microcontroller supported by Arduino IDE) which will host the debugger on a _HardwareSerial_ or _SoftwareSerial_.

The purpose of the *DebuggerSerial* class is 