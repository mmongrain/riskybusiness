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
    
    if (answer == 0) {
        // Creates a new map
        Map::Instance();
        // Ask the name of new file to create
        UI::CreateMapFile(filename);
    }
    if (answer == 1) {
        // Loads an existing map from file
        UI::GetMapfile(filename);
        Map::Instance().Load(filename);
    }
    theMapEditor();
    
    while (keepGoing) {
        UI::StatusMessage("Would you like to make another change to that file? (y/n)");
        keepGoing = UI::BinaryChoice();
        
        if (!keepGoing) {
            // If user wants to stop and save - check if map is correct
            if (VerifyMapCorrectness()){
                Map::Instance().Save(filename);
                Map::Instance().Load(filename);
            }
            // If not correct - make him correct the map
            else keepGoing = true;
        }
        if (keepGoing)
            theMapEditor();
    }
    
    // Finished task - Returns to main menu
    
}

bool MapEditor::VerifyMapCorrectness(){
    
    // Incorrect map 1: at least 1 territory doesn't belong to any continent
    std::vector<Territory*> territories = (*Map::Instance().get_territories());
    for (auto territory : territories){
        if (territory->get_continent() == NULL){
            UI::StatusMessage("Please make sure that all your territories belong to a continent. At least one doesn't.");
            return false;
        }
    }
    
    // Incorrect map 2: not a connected graph
    if (!Map::Instance().VerifyConnectivity()){
        UI::StatusMessage("Please make sure that all your territories are connected.");
        return false;
    }
    // Incorrect map 3: map has less than 6 territories, number of players can go up to 6, so each can have their own
    if (Map::Instance().get_territories()->size()<6) {
        UI::StatusMessage("Your map needs to have at least 6 territories for it to be used in the game.");
        return false;
    }
    return true;
}

void MapEditor::theMapEditor() {
    char answer;
    
    std::vector<std::string> modifications1{ "Add a new territory", "Define Adjacency between 2 territories", "Add a new Continent" };
    answer = UI::StringMenu("Modification to do", modifications1);
    
    switch (answer) {
        case 'a':
            TerritoryCreator();
            break;
        case 'b':
            AdjacencyDefiner();
            break;
        case 'c':
            ContinentCreator();
            break;
            
        default:
            break;
    }
    
    // Menu with 2 additional options if the continents vector and territories vector aren't empty
    if (Map::Instance().get_territories()->size()!=0 && Map::Instance().get_continents()->size()!=0) {
        std::vector<std::string> modifications2{ "Add a new territory", "Define Adjacency between 2 territories", "Add a new Continent", "Assign Territories to existing Continent", "Assign Continent to existing territory" };
        answer = UI::StringMenu("Modification to do", modifications2);
        
        switch (answer) {
            case 'a':
                TerritoryCreator();
                break;
            case 'b':
                AdjacencyDefiner();
                break;
            case 'c':
                ContinentCreator();
                break;
            case 'd':
                AssignTerritoriesToExistingContinent();
                break;
            case 'e':
                AssignContinentToExistingTerritory();
                break;
                
            default:
                break;
        }
    }
    
}

// Method called when the user wants to create a new Territory
void  MapEditor::TerritoryCreator() {
    
    std::string territoryName = "";
    UI::StatusMessage("Name of the new territory to create: ");
    UI::ClearBuffer();
    while (territoryName == ""){
        territoryName = UI::StringChoice();
    }
    
    while (Map::Instance().StringToTerritory(territoryName) != 0) {
        UI::StatusMessage("This territory name is already taken. Pick another name: ");
        territoryName = UI::StringChoice();
    }
    
    Territory* newTerritory = new Territory();
    newTerritory->set_name(territoryName);
    newTerritory->set_continent(NULL);
    Map::Instance().get_territories()->push_back(newTerritory);
    
    UI::StatusMessage("Territory created!");
    
    bool wantsToAssignContinent = true;
    bool wantsToCreate;
    UI::StatusMessage("Now let's assign a Continent to it, OK? (y or n)");
    wantsToAssignContinent = UI::BinaryChoice();
    
    if(wantsToAssignContinent) {
        // If the present map does not have any continents to assign
        if (Map::Instance().get_continents()->empty()) {
            UI::StatusMessage("Looks like this Map does not have any continents yet. Create one now? (y or n)");
            wantsToCreate = UI::BinaryChoice();
            if (wantsToCreate) {
                ContinentCreator();
            }
            else if (!wantsToCreate) {
                UI::StatusMessage("The map contains no continents.");
            }
        }
        // if the continents vector is not empty
        else {
            AssignContinentToTerritory(newTerritory);
            
        }
    }
    else if(!wantsToAssignContinent) {
        UI::StatusMessage("Remember you will have to assign a Continent to it later, or there will be an error.");
    }
    
}

// Method called when the user wants to define the adjacency between 2 countries
// Load .map and browse to search for the name of these 2 countries and ask to be adjacent or not
// If one or two of the territories not found, error message
void  MapEditor::AdjacencyDefiner() {
    
    bool makeEmAdjacent, makeEmNonAdjacent;
    Territory *firstTerritory, *secondTerritory;
    
    UI::StatusMessage("Enter the names of 2 territories to see their adjacency:");
    UI::ClearBuffer();
    UI::StatusMessage("Name of first territory: ");
    firstTerritory = UI::TerritoryMenu((*Map::Instance().get_territories()));
    UI::StatusMessage("Name of second territory: ");
    secondTerritory = UI::TerritoryMenu((*Map::Instance().get_territories()));
    
    // While the two names entered don't exists
    while (firstTerritory == NULL || secondTerritory == NULL) {
        UI::StatusMessage("ERROR: 1 or 2 territories couldn't be found. Please enter 2 other names: ");
        firstTerritory = UI::TerritoryMenu((*Map::Instance().get_territories()));
        secondTerritory = UI::TerritoryMenu((*Map::Instance().get_territories()));
    }
    
    // If they are adjacent
    if (firstTerritory->AreAdjacent(secondTerritory)) {
        UI::StatusMessage("These 2 territories are adjacent.");
        UI::StatusMessage("Make them nonadjacent? (y/n)");
        makeEmAdjacent = UI::BinaryChoice();
        
        if (makeEmAdjacent) {
            // Removes each from other's adjacency list
            firstTerritory->get_adjacency_list()->erase(std::remove(firstTerritory->get_adjacency_list()->begin(), firstTerritory->get_adjacency_list()->end(), secondTerritory), firstTerritory->get_adjacency_list()->end());
            secondTerritory->get_adjacency_list()->erase(std::remove(secondTerritory->get_adjacency_list()->begin(), secondTerritory->get_adjacency_list()->end(), firstTerritory), secondTerritory->get_adjacency_list()->end());
            UI::StatusMessage("From now on, these 2 territories are not adjacent.");
        }
        else {
            UI::StatusMessage("No changes have been made.");
        }
        
    }
    // If they are nonadjacent
    else {
        UI::StatusMessage("These 2 territories are nonadjacent.");
        UI::StatusMessage("Make them adjacent? (y or n)");
        makeEmNonAdjacent = UI::BinaryChoice();
        
        if (makeEmNonAdjacent) {
            // Add each territory to the other's adjacency list
            firstTerritory->get_adjacency_list()->push_back(secondTerritory);
            secondTerritory->get_adjacency_list()->push_back(firstTerritory);
            UI::StatusMessage("From now on, these 2 territories are adjacent.");
            
        }
        else {
            UI::StatusMessage("No changes have been made.");
        }
    }
    
}

// Method called when the user wants to create a new continent
void  MapEditor::ContinentCreator() {
    bool wantsToCreate, wantsToAssignTerritories;
    std::string continentName = "";
    UI::StatusMessage("Name of the new Continent to create: ");
    UI::ClearBuffer();
    while (continentName == ""){
        continentName = UI::StringChoice();
    }
    
    while (Map::Instance().StringToContinent(continentName) != 0) {
        UI::StatusMessage("This continent name is already taken. Pick another name: ");
        continentName = UI::StringChoice();
    }
    
    Continent* newContinent = new Continent();
    newContinent->set_name(continentName);
    Map::Instance().get_continents()->push_back(newContinent);
    
    UI::StatusMessage("Continent created! Now, let's assign territories to it. OK? (y/n).");
    wantsToAssignTerritories = UI::BinaryChoice();
    
    if(wantsToAssignTerritories) {
        // If the present map does not have any territories to assign
        if (Map::Instance().get_territories()->empty()) {
            UI::StatusMessage("Looks like this Map does not have any territories yet. Create one now? (y or n)");
            wantsToCreate = UI::BinaryChoice();
            if (wantsToCreate) {
                TerritoryCreator();
            }
            else if (!wantsToCreate) {
                UI::StatusMessage("The map contains no territories.");
            }
        }
        // if the territories vector is not empty
        else {
            AssignTerritoriesToContinent(newContinent);
            
        }
        
    }
    else if(!wantsToAssignTerritories) {
        UI::StatusMessage("Remember you will have to assign territories to it later, or there will be an error.");
    }
    
}


// Method to assign territories to a continent (new or existing)
void MapEditor::AssignTerritoriesToContinent(Continent* continent) {
    std::string continentName = continent->get_name();
    bool wantsToContinue = true;
    UI::StatusMessage("Here's the list of territories that you can choose from (Enter letter):");
    
    // Loop for multiple territories
    Territory* territoryToAssign;
    do {
        territoryToAssign = UI::TerritoryMenu(*Map::Instance().get_territories());
        continent->get_territories().push_back(territoryToAssign);
        UI::StatusMessage("Do you want to assign another territory to that continent? (y/n)");
        wantsToContinue = UI::BinaryChoice();
    } while (wantsToContinue);
    
    UI::StatusMessage("All the territories were assigned to "+continentName+" successfully!");
    
    
}

// Method to assign continent to territory (new or existing)
void MapEditor::AssignContinentToTerritory(Territory* territory) {
    UI::StatusMessage("Here's the list of continents you can choose from (Enter a letter):");
    Continent* assignedContinent = UI::ContinentMenu(*Map::Instance().get_continents());
    territory->set_continent(assignedContinent);
    UI::StatusMessage("Continent "+assignedContinent->get_name()+" assigned to Territory "+territory->get_name()+"!");
}

// Method called when the user wants to assign territories to existing continent
void MapEditor::AssignTerritoriesToExistingContinent() {
    Continent* theContinent;
    bool wantsToCreate;
    
    if (Map::Instance().get_territories()->empty()) {
        UI::StatusMessage("No continents exist yet. Create one now? (y or n)");
        wantsToCreate = UI::BinaryChoice();
        if (wantsToCreate) {
            ContinentCreator();
        }
        else if (!wantsToCreate) {
            UI::StatusMessage("The map contains no continents.");
        }
    }
    else {
        UI::StatusMessage("Choose from this list, the existing Continent (Enter a letter):");
        theContinent = UI::ContinentMenu(*Map::Instance().get_continents());
        
        AssignTerritoriesToContinent(theContinent);
    }
}

// Method called when the user wants to assign a continent to existing territory
void MapEditor::AssignContinentToExistingTerritory() {
    Territory* theTerritory;
    bool wantsToCreate;
    
    if (Map::Instance().get_territories()->empty()) {
        UI::StatusMessage("No territory exist yet. Create one now? (y or n)");
        wantsToCreate = UI::BinaryChoice();
        if (wantsToCreate) {
            TerritoryCreator();
        }
        else if (!wantsToCreate) {
            UI::StatusMessage("The map contains no territories.");
        }
    }
    else {
        UI::StatusMessage("Choose from this list, the existing Territory (Enter a letter):");
        theTerritory = UI::TerritoryMenu(*Map::Instance().get_territories());
        
        AssignContinentToTerritory(theTerritory);
    }
    
}
