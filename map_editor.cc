#include <iostream>
#include <string>
#include "map.h"
#include "territory.h"
#include "continent.h"
#include "map_editor.h"
#include <vector>
#include <fstream>
#include <algorithm>// std::find()
#include "ui.h"

// General opening of the Map Editor
void MapEditor::introMapEditor() {
    int answer;
    char filename[100];
    bool keepGoing = true;
    
    UI::StatusMessage("Welcome to the Interactive Map Editor.");
    UI::StatusMessage("What would you like to do?");
    UI::StatusMessage("Create a new map (Enter 0) or modify an exisiting map (Enter 1)?");
    
    answer = UI::IntChoice(0, 1);
    
    if (answer==0) {
        // Creates a new map
        Map::Instance();
        // Ask the name of new file to create
        UI::CreateMapFile(filename);
    }
    if (answer==1) {
        // Loads an existing map from file
        UI::GetMapfile(filename);
        Map::Instance().Load(filename);
    }
    theMapEditor();
    
    UI::StatusMessage("Would you like to make another change to that file? (y or n)");
    keepGoing = UI::BinaryChoice();
    
    while (keepGoing) {
        theMapEditor();
    }
    
    if (!keepGoing) {
        Map::Instance().Save(filename);
        // At this point, if the map cannot be loaded after being saved, there will be an error message
        Map::Instance().Load(filename);
    
    }
    // Finished task - Returns to main menu
    
}

void MapEditor::theMapEditor() {
    char answer;
    
    std::vector<std::string> modifications {"Add a new Country","Define Adjacency between 2 countries","Add a new Continent"};
    answer = UI::StringMenu("Modification to do", modifications);
    
    // User choice decides which modification to do
    if(answer=='a')
         CountryCreator();
    else if(answer=='b')
         AdjacencyDefiner();
    else if(answer=='c')
         ContinentCreator();

}

// Method called when the user wants to create a new country
void  MapEditor::CountryCreator() {
    
    std::string countryName;
    UI::StatusMessage("Name of the new Country to create: ");
    countryName = UI::StringChoice();
    
    while (Map::Instance().StringToTerritory(countryName)!=0) {
        UI::StatusMessage("This country name is already taken. Pick another name: ");
        countryName = UI::StringChoice();
    }
    
    Territory* newTerritory = new Territory();
    newTerritory->set_name(countryName);
    Map::Instance().get_territories()->push_back(newTerritory);
    
    UI::StatusMessage("Territory created!");
    
}

// Method called when the user wants to define the adjacency between 2 countries
// Load .map and browse to search for the name of these 2 countries and ask to be adjacent or not
// If one or two of the country not found, error message
void  MapEditor::AdjacencyDefiner() {
    
    bool makeEmAdjacent, makeEmNonAdjacent;
    std::string firstCountry, secondCountry;
    
    UI::StatusMessage("Enter the names of 2 territories to see their adjacency:");
    
    UI::StatusMessage("Name of first country: ");
    firstCountry = UI::StringChoice();
    UI::StatusMessage("Name of second country: ");
    secondCountry = UI::StringChoice();
    
    // While the two names entered don't exists
    while (Map::Instance().StringToTerritory(firstCountry)==0 || Map::Instance().StringToTerritory(secondCountry)==0) {
        UI::StatusMessage("ERROR: 1 or 2 countries couldn't be found. Please enter 2 other names: ");
        firstCountry = UI::StringChoice();
        secondCountry = UI::StringChoice();
    }
    
    Territory* aTerritory = Map::Instance().StringToTerritory(firstCountry);
    Territory* anotherTerritory = Map::Instance().StringToTerritory(secondCountry);
    
    // If they are adjacent
    if (aTerritory->AreAdjacent(anotherTerritory)) {
        UI::StatusMessage("These 2 territories are adjacent.");
        UI::StatusMessage("Make them nonadjacent? (y or n)");
        makeEmAdjacent = UI::BinaryChoice();
        
        if (makeEmAdjacent) {
            // Removes each from other's adjacency list
            aTerritory->get_adjacency_list()->erase(std::remove(aTerritory->get_adjacency_list()->begin(),aTerritory->get_adjacency_list()->end(),anotherTerritory),aTerritory->get_adjacency_list()->end());
            anotherTerritory->get_adjacency_list()->erase(std::remove(anotherTerritory->get_adjacency_list()->begin(),anotherTerritory->get_adjacency_list()->end(),aTerritory),anotherTerritory->get_adjacency_list()->end());
            UI::StatusMessage("From now on, these 2 territories are adjacent.");
        }
        else {
            UI::StatusMessage("No changes have been made.");
        }
        
    }
    // If they are not adjacent
    else {
        UI::StatusMessage("These 2 territories are nonadjacent.");
        UI::StatusMessage("Make them adjacent? (y or n)");
        makeEmNonAdjacent = UI::BinaryChoice();
        
        if (makeEmNonAdjacent) {
            // Add each country to the other's adjacency list
            aTerritory->get_adjacency_list()->push_back(anotherTerritory);
            anotherTerritory->get_adjacency_list()->push_back(aTerritory);
            UI::StatusMessage("From now on, these 2 territories are nonadjacent.");
            
        }
        else {
            UI::StatusMessage("No changes have been made.");
        }
    }
    
}

// Method called when the user wants to create a new continent
void  MapEditor::ContinentCreator() {
    bool wantsToCreate;
    std::string continentName;
    UI::StatusMessage("Name of the new Continent to create: ");
    continentName = UI::StringChoice();
    
    while (Map::Instance().StringToContinent(continentName)!=0) {
        UI::StatusMessage("This continent name is already taken. Pick another name: ");
        continentName = UI::StringChoice();
    }
        
    Continent* newContinent = new Continent();
    newContinent->set_name(continentName);
    Map::Instance().get_continents()->push_back(newContinent);
    
    UI::StatusMessage("Continent created! Now, let's see the territories that you can choose to assign to it.");
    
    // If the present map does not have any territories to assign
    if (Map::Instance().get_territories()->empty()) {
        UI::StatusMessage("Looks like this Map does not have any territories yet. Create one now? (y or n)");
        wantsToCreate = UI::BinaryChoice();
        if (wantsToCreate) {
            CountryCreator();
        }
    }
    // if the territories vector is not empty
    else {
        AssignTerritoriesToContinent(newContinent);
        
    }
    
}

void MapEditor::AssignTerritoriesToContinent(Continent* newContinent) {
    std::string continentName = newContinent->get_name();
    bool wantsToContinue = true;
    UI::StatusMessage("Here's the list of territories that you can choose from to assign to your Continent.");
    UI::DisplayTerritoriesList(Map::Instance().get_copy_territories());
    
    int numOfTerritoriesToAssign;
    int maxNumOfTerritories = Map::Instance().get_territories()->size();
    UI::StatusMessage("How many of them would you like to assign to "+continentName+"?");
    numOfTerritoriesToAssign = UI::IntChoice(0, maxNumOfTerritories);
    
    // If the user decides to add no territories
    while (numOfTerritoriesToAssign==0) {
        UI::StatusMessage("Your continent will be left empty. Do you wish to continue?");
        wantsToContinue = UI::BinaryChoice();
        // If user changed his mind by answering no
        if (!wantsToContinue) {
            UI::StatusMessage("How many of these territories would you like to assign to "+continentName+"?");
            numOfTerritoriesToAssign = UI::IntChoice(0, maxNumOfTerritories);
        }
        
    }
    // The user decides to add territories
    if (numOfTerritoriesToAssign>0) {
        std::string territoryNameToAssign;
        if (numOfTerritoriesToAssign==1) { UI::StatusMessage("Now, Enter the name of that territory: "); }
        else {UI::StatusMessage( "Now, Enter the names of those territories from the above list: "); }
        for (unsigned int i = 0; i < numOfTerritoriesToAssign; i++) {
            territoryNameToAssign = UI::StringChoice();
        
            while (Map::Instance().StringToTerritory(territoryNameToAssign)==0) {
                UI::StatusMessage("This territory does not exist. Please refer to the names in the above list:");
                territoryNameToAssign = UI::StringChoice();
            }
        
            newContinent->get_territories().push_back(Map::Instance().StringToTerritory(territoryNameToAssign));
        }
        UI::StatusMessage("All of the territories were assigned successfully!");
    }
    
}
