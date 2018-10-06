# Introduction
This library is for the receiver end of the Razor 9 DOF IMU (reference  [here](https://github.com/Razor-AHRS/razor-9dof-ahrs/tree/master/Arduino/Razor_AHRS)).

# User guide
## Downloading the library
It is suggested that you download the entire repository and then select this folder, so that you can enjoy the benifits of VCS like git. It makes it simpler to update the contents whenever patch fixes are done. You can simply open a terminal (or gitbash on windows), go to the folder where you want to save this repository and type the following command.
```
git clone https://github.com/RoboManipal-9-0/Libraries.git -b dev
```
_You might want to omit the `-b <branch>` tag if you're downloading from the master branch_.

**Not recommended**: You can download _only_ this folder by clicking [here](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/RoboManipal-9-0/Libraries/tree/Branch-Avneesh/RazorIMU_9DOF)

## Using the library with Arduino
Move this folder into the arduino libraries folder on your PC. If you don't know where the libraries folder of your arduino is, you can check out the README file of this entire repository for this, click [here](../README.md).<br>

## Prerequisites
Please follow the following steps before working with this library:
- Download the official code folder from [here](https://minhaskamal.github.io/DownGit/#/home?url=https://github.com/Razor-AHRS/razor-9dof-ahrs/tree/master/Arduino/Razor_AHRS), you'll be uploading this to the IMU.
- Extract folder *Razor_AHRS* to an appropriate location, open the *Razor_AHRS* file in Arduino IDE.
- Under the tools dropdown, select the following:
    - **Board**: Arduino Pro or Pro Mini
    - **Processor**: Atmega 328P (3.3V, 8MHz)
    - **Port**: The connected port (/dev/ttyUSB\* for Ubuntu, COM\* for windows).
- In the code of *Razor_AHRS* file, go to **USER SETUP AREA** and uncomment the correct #define HW\_\_VERSION\_CODE. It's 10736 in our examples, check the version from the correct hardware datasheet.
- Set the OUTPUT\_\_STARTUP\_STREAM\_ON to *false*. This will disable the continuous output stream.
- Upload the code.
- Open serial monitor
- Set baud rate to 57600
- There must be output

More info about setting up software  [here](https://github.com/Razor-AHRS/razor-9dof-ahrs/wiki/Tutorial#setting-up-the-software).

# Developers Guide


[![Image](https://img.shields.io/badge/Developer-TheProjectsGuy-blue.svg)](https://github.com/TheProjectsGuy)
