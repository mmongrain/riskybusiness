# Team "Risky Business (1983)" Conquest Game

## Team Members
Anne-Marie Dube, #26456383   
Matthew Mongrain, #26991793   
Tan Trung Nguyen, #26621856   
Alika Utepova, #26917046   

## State of the Project
At this stage of intermediate delivery, the game is in a playable state, but is missing some features. (This being a Risk clone, you would likely lose several hours and several friends before you discovered those missing features, however.) Following is a list of currently implemented features, a list of features still being worked on, and a list of features that will be added later, along with compilation instructions for the current set of files.

### Currently Implemented
* Human players
* Map file parsing and output
* Singleton classes for Map and Game
* Observer classes for Player and Map
* Battle and turn logic
* Main game loop

### In Progress
* Map editor
* Computer players
* Victory conditions for main game loop

### Roadmap 
* GUI using SFML
* Cards

## Compilation Instructions
A makefile is included with the files in this .zip.
```
make
```
is sufficient to compile it using gcc, and has been tested under Ubuntu Linux 14.04 and Mac OSX 10.10. Compilation has also been tested in Windows 8 using Visual Studio 2012. 

## Operation Notes
Though the program deals more or less gracefully with invalid input, there are some times where it can misbehave when reading commands from the keyboard. Since interaction with the final game will be done entirely through the mouse, we don't intend to fix text input--it's only there to demonstrate the operation of the program.

The game should work with any correctly-formatted .map file from http://www.windowsgames.co.uk/conquest_maps.html ; World.map from that site has been included for testing. For other maps, game_driver.cc would need to be modified with the new file name. The final version will have a GUI for selecting, loading, and saving maps.
