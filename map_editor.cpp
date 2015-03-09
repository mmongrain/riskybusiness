//
//  map_editor.cpp
//  COMP345-A2
//
//  Created by Leonard Nguyen on 2015-02-24.
//  Copyright (c) 2015 Leonard Nguyen. All rights reserved.
//

#include <iostream>
#include <string>
#include "map.h"
#include "map_editor.h"
#include <vector>
#include <fstream>
#include <algorithm>// std::find()

// General opening of the Map Editor
void MapEditor::introMapEditor() {
    int answer;
    char filename[100];
    std::cout << "Welcome to the Interactive Map Editor." << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "Create a new map (Enter 0) or modify an exisiting map (Enter 1)?" << std::endl;
    std::cin >> answer;
    
    if (answer==0) {
        // Creates a new map
        Map::Instance();
        // Ask the name of new file to create
        std::cout << "Name of the file (.map): " << std::endl;
        std::cin >> filename;
    }
    if (answer==1) {
        // Loads an existing map from file
        char filename[100] = "World.map";
        Map::Instance().Load(filename);
    }
    theMapEditor();
    
    Map::Instance().Save(filename);
    
    
}

void MapEditor::theMapEditor() {
    int answer;
    
    std::cout << "Enter 1 to add a new Country" << std::endl
     << "Enter 2 to define Adjacency between 2 countries" << std::endl
     << "Enter 3 to add a new Continent" << std::endl;
    std::cin >> answer;
    
    // User choice decides which modification to do
    if(answer==1)
         CountryCreator();
    else if(answer==2)
         AdjacencyDefiner();
    else if(answer==3)
         ContinentCreator();
    
    
     while (answer!=1||answer!=2||answer!=3) {
        std::cout << "Please enter an accepted value." << std::endl;
        std::cin >> answer;
    }
}

// Method called when the user wants to create a new country
void  MapEditor::CountryCreator() {
    std::string countryName;
    std::cout << "Name of the Country: ";
    std::cin >> countryName;
    // Iterates through territories to see if already exist
        while (std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), countryName)!=Map::Instance().get_territories()->end()) {
            std::cout << "This country name is already taken. Pick another name: " << std::endl;
            std::cin >> countryName;
        }
        
    Map::Territory* newTerritory = new Map::Territory;
    newTerritory->set_name(countryName);
    Map::Instance().get_territories()->push_back(newTerritory);
    
    
}

// Method called when the user wants to define the adjacency between 2 countries
// Load .map and browse to search for the name of these 2 countries and ask to be adjacent or not
// If one or two of the country not found, error message
void  MapEditor::AdjacencyDefiner() {
    int answer;
    std::string firstCountry, secondCountry;
    
    bool adjacency;
    std::cout << "Name of first country: ";
    std::cin >> firstCountry;
    std::cout << "Name of second country: ";
    std::cin >> secondCountry;
    // Iterates through territories to see if they exists
    while (std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), firstCountry)==Map::Instance().get_territories()->end()||std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), secondCountry)==Map::Instance().get_territories()->end()) {
        std::cout << "ERROR: 1 or 2 countries couldn't be found. Please enter 2 other names: " << std::endl;
        std::cin >> firstCountry;
        std::cin >> secondCountry;
    }
    Map::Territory &aTerritory, &anotherTerritory;
    aTerritory = std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), firstCountry);
    anotherTerritory = std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), secondCountry);
    // If they are adjacent
    if (aTerritory.AreAdjacent(anotherTerritory)) {
        std::cout << "These 2 territories are adjacent." << std::endl;
        std::cout << "Make them nonadjacent? (1 for yes/0 for no)" << std::endl;
        std::cin >> answer;
        if (answer==1) {
            //manipulations of nodes
        }
        
    }
    // If they are not adjacent
    else {
        std::cout << "These 2 territories are nonadjacent." << std::endl;
        std::cout << "Make them adjacent? (1 for yes/0 for no)" << std::endl;
        std::cin >> answer;
        if(answer==1) {
            //manipulations of nodes
        }
    }
    
}

// Method called when the user wants to create a new continent
void  MapEditor::ContinentCreator() {
    std::string continentName;
    std::cout << "Name of the Continent: " << std::endl;
    std::cin >> continentName;
    // Iterates to see if continent already exist
        while (std::find(Map::Instance().get_continents()->begin(), Map::Instance().get_continents()->end(), continentName)!=Map::Instance().get_continents()->end()) {
            std::cout << "This continent name is already taken. Pick another name: " << std::endl;
            std::cin >> continentName;
        }
        
    Map::Continent* newContinent = new Map::Continent;
    newContinent->set_name(continentName);
    Map::Instance().get_continents()->push_back(newContinent);
    
    
}