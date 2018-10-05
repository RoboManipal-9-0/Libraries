![Version tag](https://img.shields.io/badge/version-1.0.1-orange.svg)
# Introduction
This library is for defining and controlling an **N** omni wheel base where all the axis of the wheels pass through a central point. It's like following the euler coordinate system.

The library stands for _N Wheel Concentric Holonomic Base_.

**Note**: This library is still in developer beta, ask the developer before using.

# Index
- [Introduction](#introduction)
- [Index](#index)
- [Users Guide](#users-guide)
    - [Downloading the library](#downloading-the-library)
    - [Using the library with Arduino](#using-the-library-with-arduino)
    - [Usage of the library](#usage-of-the-library)
- [Library Explanation](#library-explanation)
- [Developers Guide](#developers-guide)
    - [Class contents](#class-contents)
        - [Protected members](#protected-members)
            - [Variables](#variables)
            - [Member functions](#member-functions)
        - [Public members](#public-members)
            - [Constructors](#constructors)
            - [Member functions](#member-functions)
- [Debugger Notifications](#debugger-notifications)
    - [Debug level](#debug-level)
    - [Info level](#info-level)

# Users Guide
## Downloading the library
It is suggested that you download the entire repository and then select this folder, so that you can enjoy the benefits of VCS like git. It makes it simpler to update the contents whenever patch fixes are done. You can simply open a terminal (or gitbash on windows), go to the folder where you want to save this repository and type the following command.
```bash
git clone https://github.com/RoboManipal-9-0/Libraries.git -b dev
```
_You might want to omit the `-b <branch>` tag if you're downloading from the master version_.

**<font color="#AA0000">Not recommended</font>** : You can download just this folder by clicking [here](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/RoboManipal-9-0/Libraries/tree/dev/NWCHBase).

## Using the library with Arduino
Move this folder into the arduino libraries folder on your PC. If you don't know where the libraries folder of your arduino is, you can check out the README file of this entire repository for this, click [here](../README.md).<br>

## Usage of the library
- Create an object of the `NWCHBase` class.
- Initialize the number of wheels that the bot has and their respective angles (in ascending order). The wheels are numbered from 1 to **N** (number of wheels) in a counter clockwise fashion, however, they're indexed from 0 to **N-1**.
    - This can be done using the constructor of the `NWCHBase` class or the _InitializeWheels_ function.
    - Pass it first the number of wheels as an integer and then the angles (in degrees) as an integer array.
- Attach the pins (PWM and DIR) of the motor driver using the _AttachPins_ function. You may configure the MaxMode using the _ConfigureMaxModeTo_ function. It's suggested that you check out the [BotBase documentation](./../BotBase/) for more.
- Call the _Move_ function to move the bot at a velocity, with some angle to the reference and having some angular velocity about the center of the bot.
<!-- TODO: Add links to the examples -->
You can check out the [examples]() for more.

# Library Explanation
Here's the **mathematical derivation**.<br>
![Mathematical Derivation](./../.DATA/Images/NWCHBase_derivation.jpg)<br>
The explanation of every term is as follows:<br>
> **θ<sub>i</sub>** is the angle the i<sup>th</sup> wheel makes with the horizontal axis.<br>
> **V<sub>i</sub>** is the velocity vector of the i<sup>th</sup> wheel.<br>
> **V** is the command velocity. This is given with respect to the vertical (as shown by the triangle with acute angle θ). This is resolved into two components (**V<sub>x</sub>** and **V<sub>y</sub>**).<br>
> **ω** or **w** is the desired angular velocity of the base with respect to the center point (where the two dashed orange lines meet).

As you can observe, these two components (**V<sub>x</sub>** and **V<sub>y</sub>**) of **V** can further be broken into parallel to the axis of the wheels and perpendicular to the axis of the wheels. We take the ones perpendicular because only they can be achieved through the actuation.<br>
Add this with ω x 1 (velocity superimposed to get the angular velocity).

# Developers Guide
This library class inherits the **BotBase** class (documentation [here](./../BotBase/)). Let's have a detailed look at the contents of the class `NWCHBase`

## Class contents
This library consists of only one class, the `NWCHBase` class. Let's explore it's contents.

### Protected members

#### Variables
- **<font color="#CD00FF">float</font> \*angles** : This is an array consisting of angles (in radians) of all the wheels (in the correct indexed order). It is basically contains the **θ<sub>i</sub>** values.

#### Member functions
- **<font color="#5052FF">void</font> <font color="#f2e165">Move_PWM_Angle</font>(<font color="#76bef2">int</font> PWM, <font color="#76bef2">float</font> angle_radians, <font color="#76bef2">float</font> w = 0)** : This function takes the velocity or _PWM_ (basically the **V** value) and the header direction angle (in radians), which is basically **θ** value. It also takes the angular velocity needed about the center of the bot (**w** or **ω** value). It calculates the velocity vector, which is all the **V<sub>i</sub>** values. It then calls the *VectorTo_PWM_DIR* function from the `BotBase` class. The user only needs to call the `Move` function of the **BotBase** class.

### Public members
#### Constructors
- **<font color="#f2e165">NWCHBase</font>()** : Empty constructor.
- **<font color="#f2e165">NWCHBase</font>(<font color="#76bef2">int</font> num_wheels)** : Takes and initializes the number of wheels to *num_wheels*.
- **<font color="#f2e165">NWCHBase</font>(<font color="#76bef2">int</font> num_wheels, <font color="#76bef2">int</font> \*angles_deg)** : Takes and initializes the number of wheels (*num_wheels*). It also initializes the angle vector (list of **θ<sub>i</sub>** values) by degree to radian conversion and then into _angles_ vector.

#### Member functions
- **<font color="#5052FF">void</font> <font color="#f2e165">InitializeWheels</font>(<font color="#76bef2">int</font> num_wheels)** : Takes and initializes the number of wheels to *num_wheels*.

- **<font color="#5052FF">void</font> <font color="#f2e165">InitializeWheels</font>(<font color="#76bef2">int</font> \*angles_deg)** : Initializes the list of **θ<sub>i</sub>** values.

- **<font color="#5052FF">void</font> <font color="#f2e165">InitializeWheels</font>(<font color="#76bef2">int</font> num_wheels, <font color="#76bef2">int</font> \*angles_deg)** : Takes and initializes the number of wheels (*num_wheels*). It also initializes the angle vector (list of **θ<sub>i</sub>** values) by degree to radian conversion and then into _angles_ vector.

**NOTE** : *angles_deg* is an array of angles in *degrees*. The degree to radian conversion is something the user needn't worry about. The library takes care of that.

# Debugger Notifications
Here are the messages that the library might send out onto the debugger. This library inherits the entire debugger from the `BotBase` library.

## Debug level
1. **Move_PWM_Angle** function<br>
Sends out the PWM vector
    ```bash
    Wheel motion vector: %val1% %val2% %val3% ... %valN%
    ```
    **For example:** <br>
    - For four wheels (don't pay attention to the values, they're arbitrary)
        ```bash
        Wheel motion vector: 76 54 -76 -54
        ```

## Info level
1. **InitializeWheels** function<br>
    Sends out an info message that the wheels have been initialized (it only notifies you about the angle vector)
    ```bash
    Initializing angle configuration: %ang1_deg%(%ang1_rad%) %ang2_deg%(%ang2_rad%) ... %angN_deg%(%angN_rad%)
    ```
    **For example:**<br>
    - For a four wheel bot
        ```bash
        Initializing angle configuration: 45(0.785398) 135(2.356194) 225(3.926990) 315(5.497787)
        ```
    - For a three wheel bot
        ```bash
        Initializing angle configuration: 90(1.570796) 210(3.665191) 330(5.759586)
        ```

[![Image](https://img.shields.io/badge/developed%20using-VSCode-lightgrey.svg)](https://code.visualstudio.com/)
[![Image](https://img.shields.io/badge/Developer-TheProjectsGuy-blue.svg)](https://github.com/TheProjectsGuy)
[![Spawning issue](https://img.shields.io/badge/issue-%236-green.svg)](https://github.com/RoboManipal-9-0/Libraries/issues/6)