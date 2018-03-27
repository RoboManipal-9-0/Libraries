# Libraries
The set of personal libraries RoboManipal 9.0 uses

##############################################################
################### NOTE FOR USERS ###########################
##############################################################
Just download the repository and move the desired file to the include folder of Arduino on your system.
On Ubuntu, it's ~/Arduino/libraries (Check the $sketchbook location$/libraries folder)


##############################################################
################# NOTE FOR DEVELOPERS ########################
##############################################################
Add all your files in folders having approprite names here
(Individual people have their own branches, codes are later pulled)

Follow the following procedure (To create a Library named 'Sample')
- All your class declaration (all the methods and variable declaration) happen in a header file named 'Sample.h'
  - Be sure you include "Arduino.h" to use general arduino functions (check the hardware folder for main functions
- In the CPP file named 'Sample.cpp', write the code of all these functions (using the :: operator to define member functions outside class)
  - Bu sure you include the header file first, so that you can use the class
- It is highly suggested that you use a 'keywords.txt' and a 'README.txt'. Classes are KEYWORD1 and functions are KEYWORD2 type, you can try LITERAL1 if needed
- Place the files in a folder named 'Sample' and move it to ~/Arduino/Libraries (for Ubuntu/Linux users). Alternatively, you could movo the entire repository there (not recommended, instead put individual files there)
