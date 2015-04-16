# Risky Business (1983)

## Introduction
Risky Business (1983) is a Risk clone controllable entirely from the command line. It features a GUI mode, three levels of AI difficulty, a map editor, and compatibility with .map files from Sean O'Connor's game [Conquest](http://www.windowsgames.co.uk/conquest.html).

## Compilation
Risky Business was written with cross-platform compatibility in mind, and compiles and runs well on Linux, Mac OSX, and Windows. Regardless of your platform, you will need to satisfy two library dependencies before compilation, namely
* [Boost](http://www.boost.org)
* [SFML](http://www.sfml-dev.org/index.php)

On Linux, these libraries can be installed through your favorite package manager, and on Windows by following the instructions on the sites above. The source was written with gcc 4.2.2 in mind; we have not tested compilation with other compilers.

We've included a makefile with the source and tests. On Linux, 
````
make
````
will compile everything nicely into an executable called rb.o, which can be run by typing
````
./rb.o
````
If you run into any problems compiling or running the unit tests or software, please [let me know](mailto:mtmngrn@gmail.com) and I’ll do everything I can to help. In case you really run into trouble, in which case I’ll assume you’re running Windows ;), try running RiskIsAwesome3/Release/RiskIsAwesome3.exe, which should work out-of-the-box on Windows 7/8.

## Unit Testing
Our two unit testing modules (Deck and Map) can be found, along with all the files each needs to run and compile, in unit-deck/ and unit-map/ respectively. We have included source code alone so that you can compile and test the code using your preferred OS and environment.

## Options
On launching the game, you'll see an options menu. GUI mode is off by default, but it makes the game a *lot* easier to play and has a pretty colour scheme, too.
* *"GUI" mode (off by default)*: Launches an SFML GUI window with the game board and pieces to help visualize the game. Requires that the .map file be joined to an appropriate .bmp file in the same directory as the executable.
* *Verbose mode (off by default)*: Prints every time an object changes. Annoying.
* *GUI Map Labels (on by default)*: Prints labels with name, controlling player, and units on territories. Requires GUI mode.
* *GUI Author Info (off by default)*: Prints the author information of the .map file in the top left corner of the window.
* *Gladiator Mode (off by default)*: Pits six AI players of varying difficulties against one another in a match to the death for your entertainment. Highly entertaining in combination with GUI mode and Slow Mode Off.
* *Slow Mode (on by default)*: Slows down the AI players' text scroll to give you a chance to see what's going on.

## Help
An ingame command reference can be summoned at any time by pressing ? and hitting RETURN. That's also how you quit the game.

## GitHub
The project’s [GitHub page](https://github.com/mmongrain/riskybusiness/) is a good place to get the latest version.

## Credits
Risky Business (1983) was written by [Matthew Mongrain](https://github.com/mmongrain), [Alika Utepova](https://github.com/AlikaU) and Tan Trung Nguyen.

