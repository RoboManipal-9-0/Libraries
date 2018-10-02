# How to contribute
I'm really glad you're reading this. This repository is maintained by the coding subsystem of team RoboManipal.<br>
We want you working on things that you're excited about.

Before you get started, here are some important resources:
- Arduino reference [here](https://www.arduino.cc/reference/en/), [website](https://www.arduino.cc/) and [download](https://www.arduino.cc/en/Main/Software)
- Arduino resources [here](https://playground.arduino.cc/main/resources)
- Git [documentation](https://git-scm.com/docs) and [cheatsheet](https://services.github.com/on-demand/downloads/github-git-cheat-sheet.pdf)

You might need them time to time.

# Testing
All the libraries on the `master` branch are tested on the Arduino IDE by RoboManipal. You can also test them personally, send us a proof of work and your library too will be on the master branch.

## Minimum requirements
There are some basic requirements that your library must satisfy
- Documentation for all the libraries is mandatory, all the libraries must have a `README.md` file. This serves as the documentation for the library.
- All developers must read the [README](../README.md) file of this repository.
- It's suggested that you use appropriate naming conventions for all your identifiers. Also, have a readable code well explained with comments.
- All the developed libraries must have a debugger for debugging purposes. It's suggested that you use a Serial to do so.

### Document your library
You are also suggested to make useful documentation of all the libraries that you make. All the documentations must have the following standards:
- All libraries must have a `README.md` file written in GitHub markdown. All documentation about the library goes here
- A `Users Guide` section and a `Developers Guide` section.
    - In `Users Guide`, please explain how a user can use the library and about an example (if you have any). It must have the following tags
        - `Downloading the library` where you explain how to download the library and it's dependencies.
        - `Using the library with Arduino` where you explain how to set up the library in Arduino. (Mention `Prerequisites` if any).
        - `Examples` if you've created any.
    - The `Developers Guide` has info about all the code you've written. It must have the following tags
        - `Library Details` which must have
            - `Files in the library` which will have separate headers for every file followed by description.
        - `Class description` which describes everything within your class (library class). It must have headers for `private members`, `public members` and `protected members`, with each having their own headers for `constructors`, `member functions` and `variables`.
- It is also suggested that you include the derivation if the library has a mathematical foundation.
- **Developer Shield** in the end: All documentation files must have a developer stamp (a developer shield) in the end to show who worked on the library, the stamp must link to the GitHub profile of the developer. The shield must have _developer_ subject and the GitHub ID as the _status_ in blue color. You could use [this website](https://shields.io/#/) for creating shields.
