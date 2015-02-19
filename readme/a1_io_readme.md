README

IDE used: XCode Version 6.1.1 for Mac

NOTE: If opened with XCode, the .map file created/saved is in the same folder as in executable file in the debug folder.

COMP345 - Assignment 1
Part Chosen: 4)Save/Load

Creation: Analysis & Design
--------------------------------

I decided to create an IORisk class that contains any functions or methods needed for any transfer of data between a .map text file and the program.

For now, the IORisk class contains 2 methods: save() and load().

The save() method open/imports the World.map file. First, the data get tranferred into a multidimensional array. I wasn't sure of what had to be changed exactly in the file so I gave the user the choice to decide which element/data he/she wanted to change by taking 2 different indexes (i,j) one for each dimension of the arrays. These indexes will also be the parameters for the save() method. An input string will also be one of the parameters for the modification. The chosen element from the array gets changed to the user input. Finally, the whole array gets transferred back into the World.map file.
This method does not work...

The load() method open/imports the World.map file and just take whatever is in it and outprints it, I also wanted the data to be stored in Multidimensional Dynamic Array but got confused as to how to put the right amount of elements in each array of each dimension after spliting the content of the file as a string, so my partial work is put as comments for that part.
This method work!

A Country class was created to implement the array of a Map Object.

A Player class was also created, in case I needed one.



The Driver
------------

I tried to keep it simple. Taking an input by the user for if he/she wants to load or save. For the save() part, the user have to provide 3 indexes to find the exact element to be changed.