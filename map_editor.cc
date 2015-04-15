#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>// std::find()

#include "map.h"
#include "territory.h"
#include "continent.h"
#include "map_editor.h"
#include "ui.h"

void MapEditor::StartMapEditor() {
    std::vector<std::string> main_options{
        "Return to main menu",   // 0
        "Create a new map",      // 1
        "Modify an existing map" // 2
    };
    while (true) {
        int answer = UI::StringMenu("INTERACTIVE MAP EDITOR", main_options);
        switch (answer) {
            case 0:
                return;
            case 1:
                NewMap();
                break;
            case 2:
                ExistingMap();
                break;
        }
    }
}

void MapEditor::NewMap() {
  std::ifstream f;
  UI::ClearBuffer();
  std::string filename = UI::StringChoice("What filename do you want to use for your new map?");
  while (filename == "" || filename == "\n") {
    filename = UI::StringChoice("Invalid filename--please try again!");
  }
  Map::Instance().map_info.filename = filename;
  std::string author = UI::StringChoice("What's the name of the author?");
  while (author == "" || author == "\n") {
    author = UI::StringChoice("Invalid name--please try again!");
  }
  Map::Instance().map_info.author = author;
  std::string image = UI::StringChoice("What's the filename of the associated .bmp image?\nEnter 'none' for none.");
  while (image == "" || image == "\n") {
  author = UI::StringChoice("Invalid filename--please try again!");
  }
  Map::Instance().map_info.image = image;
  Map::Instance().map_info.wrap = UI::BinaryChoice("Wrap (y/n)? Enter n if you don't know or don't care.");
  Map::Instance().map_info.scroll = UI::BinaryChoice("Scroll (y/n)? Enter n if you don't know or don't care.");
  Map::Instance().map_info.warn = UI::BinaryChoice("Warn (y/n)? Enter n if you don't know or don't care.");
  NewMapContinents();
  NewMapTerritories();
  NewMapAdjacencies();
  EditMenu();
}

void MapEditor::ExistingMap() {
  std::ifstream f;
  UI::ClearBuffer();
  std::string filename = UI::StringChoice("What filename do you want to load?");
  while (filename == "" || filename == "\n") {
    filename = UI::StringChoice("Invalid filename--please try again!");
  }
  Map::Instance().Load(filename.c_str());
  EditMenu();
}

void MapEditor::NewMapContinents() {
  std::vector<std::string> continents_options {
    "Add a continent",
    "Delete a continent",
    "Continue to next step",
  };
  while (true) {
    int answer = UI::StringMenu("STEP 1: DEFINE CONTINENTS", continents_options);
    switch (answer) {
      case 0: 
        AddContinent();
        break;
      case 1:
        if (Map::Instance().continents.size() > 0) {
          RemoveContinent();
        } else {
          UI::StatusMessage("You haven't created any continents to delete yet!");
        }
        break;
      case 2: 
        if (Map::Instance().continents.size() > 1) {
          return;
        } else {
          UI::StatusMessage("You need to create at least two continents!");
          break;
        }
    }
  }
}

void MapEditor::NewMapTerritories() {
  std::vector<std::string> territories_options {
    "Add a territory",
    "Delete a territory",
    "Continue to next step",
  };
  while (true) {
    int answer = UI::StringMenu("STEP 2: DEFINE TERRITORIES", territories_options);
    switch (answer) {
      case 0: 
        AddTerritory();
        break;
      case 1:
        if (Map::Instance().territories.size() > 0) {
          RemoveTerritory();
        } else {
          UI::StatusMessage("You haven't created any territories to delete yet!");
        }
        break;
      case 2: 
        if (Map::Instance().territories.size() > 5) {
          return;
        } else {
          UI::StatusMessage("You need to create at least six territories!");
          break;
        }
    }
  }
}

void MapEditor::AddContinent() {
  Continent *new_continent = new Continent();
  UI::ClearBuffer();
  std::string continent_name = UI::StringChoice("What's the name of your continent?");
  while (continent_name == "" || continent_name == "\n") {
    continent_name = UI::StringChoice("Invalid name--please try again!");
  }
  new_continent->name = continent_name;
  new_continent->bonus = UI::IntChoice("What's the bonus associated with " + continent_name + "? (0-100)", 0, 100);
  Map::Instance().continents.push_back(new_continent);
}

void MapEditor::AddTerritory() {
  Territory *new_territory = new Territory();
  UI::ClearBuffer();
  std::string territory_name = UI::StringChoice("What's the name of your territory?");
  while (territory_name == "" || territory_name == "\n") {
    territory_name = UI::StringChoice("Invalid name--please try again!");
  }
  new_territory->name = territory_name;
  new_territory->x = UI::IntChoice("What's the x-coordinate of " + territory_name + "? (0-1920)", 0, 1920);
  new_territory->y = UI::IntChoice("What's the y-coordinate of " + territory_name + "? (0-1080)", 0, 1080);
  UI::StatusMessage("Which continent does " + territory_name + " belong to?");
  new_territory->continent = UI::ContinentMenu(Map::Instance().continents);
  Map::Instance().territories.push_back(new_territory);
}

void MapEditor::RemoveContinent() {
  UI::StatusMessage("Remove which continent?");
  Continent *old_continent = UI::ContinentMenu(Map::Instance().continents);
  Map::Instance().continents.erase(std::remove(Map::Instance().continents.begin(), Map::Instance().continents.end(), old_continent), Map::Instance().continents.end());
  delete old_continent;
  UI::StatusMessage("Continent removed!");
}

void MapEditor::RemoveTerritory() {
  UI::StatusMessage("Remove which territory?");
  Territory *old_territory = UI::TerritoryMenu(Map::Instance().territories);
  Map::Instance().territories.erase(std::remove(Map::Instance().territories.begin(), Map::Instance().territories.end(), old_territory), Map::Instance().territories.end());
  delete old_territory;
  UI::StatusMessage("Territory removed!");
}

void MapEditor::NewMapAdjacencies() {
  std::vector<std::string> adjacency_options {
    "Establish new adjacency", // 0
    "Finish and Save Map" // 1
  };
  while (true) {
    int answer = UI::StringMenu("STEP 3: ESTABLISH ADJACENCIES", adjacency_options);
    switch (answer) {
      case 0:
        NewAdjacency();
        break;
      case 1:
        if (Map::Instance().VerifyConnectivity()) {
          if (SaveMap() ) {
            return;
          }
        } else {
          UI::StatusMessage("Your map is not fully connected yet! Please add more links.");
        }
    }
  }
}
  
void MapEditor::NewAdjacency() {
  Territory* first;
  Territory* second;
  UI::StatusMessage("Which is the first territory?");
  first = UI::TerritoryMenu(Map::Instance().territories);
  UI::StatusMessage("Which is the second territory?");
  second = UI::TerritoryMenu(Map::Instance().territories);
  if (first == second) {
    UI::StatusMessage("A territory can't be adjacent to itself!");
    return;
  } else if (std::find(first->adjacency_list.begin(), first->adjacency_list.end(), second) != first->adjacency_list.end()) {
    UI::StatusMessage("Those territories are already adjacent!");
    return;
  }
  if (UI::BinaryChoice("Define adjacency between " + first->name + " and " + second->name + " (y/n)?")) {
      first->adjacency_list.push_back(second);
      second->adjacency_list.push_back(first);
  }
}

bool MapEditor::SaveMap() {
  if (VerifyMapCorrectness()) {
    Map::Instance().Save(Map::Instance().map_info.filename.c_str());
    UI::StatusMessage("Save complete!");
    return true;
  } else return false;
}

void MapEditor::EditMenu() {
  std::vector<std::string> edit_menu_options {
    "Add a territory",  // 0
    "Remove a territory", // 1
    "Define adjacency between territories", // 2
    "Add a continent",  // 3
    "Remove a continent", // 4 
    "Save map to disk", // 5
    "Return to Map Editor main menu" // 6
  };
  while (true) {
    int answer = UI::StringMenu("EDIT MAP", edit_menu_options);
    switch (answer) {
      case 0:
        AddTerritory();
        break;
      case 1:
        RemoveTerritory();
        break;
      case 2:
        NewAdjacency();
        break;
      case 3:
        AddContinent();
        break;
      case 4:
        RemoveContinent();
        break;
      case 5:
        SaveMap();
        break;
      case 6:
        return;
    }
  }
}

bool MapEditor::VerifyMapCorrectness() {
    
    // Incorrect map 1: at least 1 territory doesn't belong to any continent
    std::vector<Territory*> territories = (*Map::Instance().get_territories());
    for (auto territory : territories) {
      if (territory->get_continent() == NULL) {
        UI::StatusMessage("Please make sure that all your territories belong to a continent! " + territory->name + ", for one, doesn't.");
        return false;
      }
    }
    // Incorrect map 2: not a connected graph
    if (!Map::Instance().VerifyConnectivity()){
        UI::StatusMessage("Please make sure that all your territories are connected!");
        return false;
    }
    // Incorrect map 3: map has less than 6 territories, number of players can go up to 6, so each can have their own
    if (Map::Instance().get_territories()->size()<6) {
        UI::StatusMessage("Your map needs to have at least 6 territories for it to be used in the game. It currently has " + std::to_string(Map::Instance().territories.size()) + ".");
        return false;
    }
    return true;
}