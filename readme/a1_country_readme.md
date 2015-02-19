COMP 345 - Assignment 1 (Part 1: Maps)
February 6, 2015
Anne-Marie Dube, 26456383

1. Compilation Instructions
My project was coded and compiled using Visual Studio 2012.
By opening the zip folder named 'Risk-Assignment1' you should be able to then import the project
into visual studio and compile, or you can just compile through commandline on Linux.

2. Design rationale
I designed the Maps part of the project in such a way that the countries and continents
are specified before hand, and the links are made between them through a function that
adds an edge between the two, and stores all the data into an Adjacency List.

The countries have attributes such as what Continent it belongs to, what player occupies it
and what the size of the army is. The latter two attributes are determined by the battle system and
thus I did not include the methods in my actual code.

The countries/continents I used come from the Lord of the Rings map, and they are just temporary
until we actually get map data later on.