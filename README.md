# Libraries
The set of personal, low level arduino libraries that RoboManipal uses.

## NOTE FOR USERS

Just download the repository and move the desired file to the include folder of Arduino on your system.
On Ubuntu, it's ~/Arduino/libraries (Open the arduino app and check the $sketchbook location$/libraries folder)<br>
Note : The main branch is the stable branch. Any other branches are developer branches, ask the developers before using code from those branches. Please don't use the libraries in the ARCHIVES folder, the support for them has been discontinued.

Please read the README file for any library before using them.


## NOTE FOR DEVELOPERS
You are required to go through the [code of conduct](./.github/CODE_OF_CONDUCT.md) and [contributing](./.github/CONTRIBUTING.md) files first.

### Creating a library
Add all your files in folders having approprite names here
(Individual people have their own branches, codes are later pushed to github and merged on master branch)

Follow the following procedure (To create a Library named `Sample`)
- All your class declaration (all the methods and variable declaration) happen in a header file named *Sample.h*
  - Be sure you include *Arduino.h* to use general arduino functions (check the hardware folder for main functions)
  - It's a good practice to have guard code to prevent importing your library more than once.
- In the CPP file named *Sample.cpp*, write the code of all these functions (using the :: operator to define member functions outside class)
  - Be sure you include the header file first, so that you can use the class
- It is highly suggested that you use a *keywords.txt* and a *README.txt* (or a *REAMDE.md*). For keywords, classes are KEYWORD1 and functions are KEYWORD2 type, you may use LITERAL1 for constants if needed. Check the [contributing](./.github/CONTRIBUTING.md) file for protocols to follow when making a README files.
- Place the files in a folder named `Sample` and move it to ~/Arduino/Libraries (for Ubuntu/Linux users). Alternatively, you could move the entire repository there (not recommended, instead put individual folders there if you don't want to include everything).
- If needed, add an examples folder inside `Sample` folder, add some example codes there.

Additional help on arduino libraries [here](https://www.arduino.cc/en/hacking/libraries).


### Resources

- [GitHub Markdown](https://guides.github.com/features/mastering-markdown/) for help regarding markdown.
- [Atom](https://atom.io) as the _recommended_ editor for development (you're free to use anything that you're comfortable with).
- [LaTeX Editor](https://www.codecogs.com/latex/eqneditor.php) for mathematical equations. _You'll have to attach the rendered equations as pictures for now_.
- [Shields](https://shields.io/#/) for creating your custom developer shields. It's suggested that you create your own custom **static** shields for putting up in the end of your `README.md` files.
