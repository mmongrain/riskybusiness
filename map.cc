#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm> //std::find()
#include <set>

#include "continent.h"
#include "map.h"
#include "player.h"
#include "territory.h"

void Map::Load(char* filename) {
  std::ifstream file(filename);
  std::vector<std::string> section_map;
  std::vector<std::string> section_continents;
  std::vector<std::string> section_territories;
  std::string input;

  // Eat any blank lines before [Map], ensure [Map] exists, eat [Map]:
  while (getline(file, input) && input.find("[Map]") == std::string::npos);

  // Read the contents of [Map] to a vector, eat [Continents] 
  while (getline(file, input) && input.find("[Continents]") == std::string::npos) {
    if (input.length() >= 3) { // Minimum protection against incorrect formatting
      section_map.push_back(input);
    } 
  }

  // Read the contents of [Continents] to a vector, eat [Territories];
  while (getline(file, input) && input.find("[Territories]") == std::string::npos) {
    if (input.length() >= 3) {
      section_continents.push_back(input);
    }
  }

  // Read the contents of [Territories] to a vector:
  while (getline(file, input)) {
    if (input.length() >= 9) { // Shortest correctly-formated line is N,x,y,C,A
      section_territories.push_back(input);
    }
  }

  Clear();
  ParseMapInfo(section_map);
  ParseContinentInfo(section_continents);
  ParseTerritoryInfo(section_territories);
  ReconcileTerritories();
  if (VerifyConnectivity()) {
    std::cout << "Map is connected!" << std::endl;
  } else {
    std:: cout << "Map is not connected!" << std::endl;
  }
} 

void Map::Save(char *filename) {
  std::ofstream out(filename);
  out << "[Map]\nauthor=" << get_author() << "\nwarn="; 
  (get_warn()) ? out << "yes\nimage=" : out << "no\nimage="; 
  out << get_image() << "\nwrap=";
  (get_wrap()) ? out << "yes\nscroll=" : out << "no\nscroll=";
  std::string scroll;
  switch (get_scroll()) {
    case 'h': scroll = "horizontal";
              break;
    case 'v': scroll = "vertical";
              break;
    default:  scroll = "none";
              break;
  }
  out << scroll << "\n\n[Continents]\n"; 
  for (unsigned int i = 0; i < continents.size(); i++) {
    out << continents[i]->ToString() << std::endl;
  }
  out << "\n[Territories]\n";
  for (unsigned int j = 0; j < territories.size(); j++) {
    out << territories[j]->ToString() << std::endl;
  }
}

void Map::Clear() {
    map_info.author = "";
    map_info.image = "";
    map_info.wrap = true;
    map_info.scroll = 'n';
    map_info.warn = true;
    territories.clear();
    continents.clear();
}

     

void Map::ParseMapInfo(const std::vector<std::string> &section_map) {
  for (unsigned int i = 0; i < section_map.size(); i++) {
    std::size_t delim = section_map[i].find("=");
    int end_of_string = section_map[i].length() - delim; 
    std::string field = section_map[i].substr(0, delim);
    boost::trim(field);
    std::string value = section_map[i].substr(delim + 1, end_of_string);
    boost::trim(value);

    if (boost::iequals(field, "author")) { // "If strings are identical" 
      map_info.author = value;

    } else if (boost::iequals(field, "image")) {
      map_info.image = value;

    } else if (boost::iequals(field, "wrap")) {
      map_info.wrap = (boost::iequals(value, "yes"));
    
    } else if (boost::iequals(field, "scroll")) {
      if (boost::iequals(value, "horizontal")) {
        map_info.scroll = 'h';
      } else if (boost::iequals(value, "vertical")) {
        map_info.scroll = 'v';
      } else {
        map_info.scroll = 'n';
      }

    } else if (boost::iequals(field, "warn")) {
      map_info.warn = boost::iequals(value, "yes");
    }
  }
}

void Map::ParseContinentInfo(const std::vector<std::string> &section_continents) {
  for (unsigned int i = 0; i < section_continents.size(); i++) {
    std::size_t delim = section_continents[i].find("=");
    Continent *continent = new Continent;
    continent->name = section_continents[i].substr(0, delim);
    boost::trim(continent->name);
    // stoi is available in c++11, make sure your compiler supports, it converts int to str
    // compilation flag is -std=c++11
    continent->bonus = std::stoi(section_continents[i].substr(delim + 1));
    // std::cout << continent << std::endl;
    continents.push_back(continent);
  }
}

void Map::ParseTerritoryInfo(const std::vector<std::string> &section_territories) {
  for (unsigned int i = 0; i < section_territories.size(); i++) {

    // territories.clear();
    Territory *temp = new Territory;
    std::vector<std::string> territory;
    std::stringstream input(section_territories[i]);
    std::string token;
    while (getline(input, token, ',')) {
      boost::trim(token);
      territory.push_back(token);
    }

    // Write to the territory struct and add it to the master territories list
    temp->name = territory[0];
    temp->x = std::stoi(territory[1]);
    temp->y = std::stoi(territory[2]);

    // Find the continent it belongs to
    for (int j = 0; j < continents.size(); j++) {
      //  boost::iequals returns true if two strings are equal ignoring case
      if (boost::iequals(continents[j]->get_name(), territory[3])) {
        temp->continent = continents[j];
        continents[j]->get_territories().push_back(temp);
      }
    }
    if (temp->continent == NULL) {
      std::cout << "Error in ParseTerritoryInfo: Continent not found for "
                << temp->name << std::endl;
    }
    for (unsigned int j = 4; j < territory.size(); j++) {
      Territory *land = new Territory();
      land->name = territory[j];
      boost::trim(land->name);
      temp->adjacency_list.push_back(land);
    }
    territories.push_back(temp);
  }
}

// This function ensures the adjacency lists of every territory point to the
// unique copy in the master territories vector
void Map::ReconcileTerritories() {
  for (unsigned int i = 0; i < territories.size(); i++) {
    for (unsigned int j = 0; j < territories[i]->adjacency_list.size(); j++) {
      for (unsigned int k = 0; k < territories.size(); k++) {
        if (territories[i]->adjacency_list[j]->name.compare(territories[k]->name) == 0) {
          Territory *temp = territories[i]->adjacency_list[j];
          territories[i]->adjacency_list[j] = territories[k];
          delete temp;
          temp = 0;
        }
      }
    }
  }
}

Territory* Map::StringToTerritory(std::string s) {
	Territory *territory;
	for (int i = 0; i < territories.size(); i++) {
		if (territories[i]->get_name().compare(s) == 0) {
			territory = territories[i];
		  return territory;	
    }
  }
	return 0;
}

bool Map::VerifyAdjacency(Territory *first, Territory *second) {
  bool left = false;
  bool right = false;
  for (auto territory : second->adjacency_list) {
    if (territory == first) { 
      left = true;
    }
  }
  for (auto territory : first->adjacency_list) {
    if (territory == second) {
      right = true;
    }
  }
  return left && right;
}

bool Map::VerifyConnectivity() {
  // First verify every node is reflexively connected to every node in it
  // adjacency_list
  std::map<Territory*, bool> traversal;
  for (auto territory : territories) { 
    traversal.emplace(territory, false);
    for (auto adjacent : territory->adjacency_list) {
      if (!VerifyAdjacency(territory, adjacent)) { return false; }
    }
  }
  // Then do a DFS to verify weak connectivity
  std::vector<Territory*> to_search;
  to_search.push_back(territories[0]);
  Territory* terr;
  while (!(to_search.empty())) {
    terr = to_search.back();
    to_search.pop_back();
    if (!traversal[terr]) {
      traversal[terr] = true;
      for (auto adjacent : terr->adjacency_list) {
        to_search.push_back(adjacent);
      }
    }
  }
  // If any of the vertices were not visited, return false
  for (auto key : traversal) {
    if (!(key.second)) {
      return false;
    }
  }
  return true;
}
    
    
















