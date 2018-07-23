# Libraries
The set of personal libraries RoboManipal uses

###### NOTE FOR USERS #####
Just download the repository and move the desired file to the include folder of Arduino on your system.
On Ubuntu, it's ~/Arduino/libraries (Open the arduino app and check the $sketchbook location$/libraries folder)
Note : The main branch is the stable branch. Any other branches are developer branches, downloading codes from there is not recommended, unless for testing purposes. Use the main branch.


#### NOTE FOR DEVELOPERS ####
Add all your files in folders having approprite names here
(Individual people have their own branches, codes are later pushed to github and merged on master branch)

Follow the following procedure (To create a Library named 'Sample')
- All your class declaration (all the methods and variable declaration) happen in a header file named 'Sample.h'
  - Be sure you include "Arduino.h" to use general arduino functions (check the hardware folder for main functions)
- In the CPP file named 'Sample.cpp', write the code of all these functions (using the :: operator to define member functions outside class)
  - Be sure you include the header file first, so that you can use the class
- It is highly suggested that you use a 'keywords.txt' and a 'README.txt'. Classes are KEYWORD1 and functions are KEYWORD2 type, you can try LITERAL1 if needed
- Place the files in a folder named 'Sample' and move it to ~/Arduino/Libraries (for Ubuntu/Linux users). Alternatively, you could move the entire repository there (not recommended, instead put individual files there if you don't want to include everything).
