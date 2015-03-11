#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm> //std::find()

#include "player.h"
#include "map.h"

std::string Map::Continent::ToString() {
  std::string out = "";
  out = get_name() + "=" + std::to_string(get_bonus());
  return out;
}

std::string Map::Territory::ToString() {
  std::string out = name + "," + std::to_string(x) + "," + std::to_string(y)
                    + "," + continent->get_name() + ",";
  for (unsigned int i = 0; i < adjacency_list.size(); i++) {
    out = out + adjacency_list[i]->name; 
    if (i < adjacency_list.size() - 1) {
      out = out + ",";
    }
  }
  return out;
}

bool Map::Territory::AreAdjacent(Map::Territory *bordering) {
  std::string border_name = bordering->get_name();
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_name().compare(border_name)) { return true; }
  }
  return false;
}

bool Map::Territory::AttackIsValid(Map::Territory *defending) {
  Map::Territory *attacking = this;
	for (unsigned int i = 0; i < Map::Instance().territories.size(); i++){
		if (defending->owner == attacking->owner){
			std::cout << "You can't attack your own people!";
			return false;
		}
		else if (defending->num_units < 1) {
			std::cout << "This country is empty!";
			return false;
		}
		else if (!attacking->AreAdjacent(defending)){
			std::cout << "Those two countries are not adjacent!";
			return false;
		}
	}
  return true;
}

bool Map::Territory::CanAttack() {
  if (this->num_units < 2) { return false; }
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() != this->owner) { return true; }
  }
  return false;
}

bool Map::Territory::CanFortify() { 
  if (this->num_units < 2) { return false; }
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() == this->owner) { return true; }
  }
  return false;
}
  
void Map::Territory::PrintAdjacentTerritories() {
  for (int i = 0; i < adjacency_list.size(); i++) {
    std::cout << adjacency_list[i]->get_name() << " (" 
              << adjacency_list[i]->get_num_units() << ", Player " 
              << adjacency_list[i]->get_owner()->get_id() << ")";
    (i < adjacency_list.size() - 1) ? std::cout << ", " : std::cout << ".\n";
  }
}

void Map::Territory::PrintAttackableTerritories(Player* player) {
  std::vector<Map::Territory*> attackable;
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() != player) {  
      attackable.push_back(adjacency_list[i]);
    }
  }
  for (int i = 0; i < attackable.size(); i++) {
    if (attackable[i]->get_owner() != player) {  
      std::cout << attackable[i]->get_name() << " (" 
                << attackable[i]->get_num_units() << ", Player " 
                << attackable[i]->get_owner()->get_id() << ")";
      (i < attackable.size() - 1) ? std::cout << ", " : std::cout << ".\n";
    }
  }
}

void Map::Territory::PrintAdjacentOwnedTerritories(Player* player) {
  std::vector<Map::Territory*> owned;
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() == player) {  
      owned.push_back(adjacency_list[i]);
    }
  }
  for (int i = 0; i < owned.size(); i++) {
    if (owned[i]->get_owner() == player) {  
      std::cout << owned[i]->get_name() << " (" 
                << owned[i]->get_num_units() << ", Player " 
                << owned[i]->get_owner()->get_id() << ")";
      (i < owned.size() - 1) ? std::cout << ", " : std::cout << ".\n";
    }
  }
}


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

  ClearMap();
  ParseMapInfo(section_map);
  ParseContinentInfo(section_continents);
  ParseTerritoryInfo(section_territories);
  ReconcileTerritories();
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

void Map::ClearMap() {
    map_info.author = "";
    map_info.image = "";
    map_info.wrap = true;
    map_info.scroll = 'n';
    map_info.warn = true;
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
    // continents.clear();
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

void Map::ReconcileTerritories() {
  /**
   * TODO: Write a better algorithm than this O(n^3) piece of junk
   * if that's even possible lol
   **/
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

Map::Territory *Map::StringToTerritory(std::string s) {
	Map::Territory *territory;
	for (int i = 0; i < territories.size(); i++) {
		if (territories[i]->get_name().compare(s) == 0) {
			territory = territories[i];
		  return territory;	
    }
  }
	return 0;
}

/*/ --Beginning of Map Editor--
// General opening of the Map Editor
void Map::introMapEditor() {
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

void Map::theMapEditor() {
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
void  Map::CountryCreator() {
    std::string countryName;
    std::cout << "Name of the Country: ";
    std::cin >> countryName;
    // Iterates through territories to see if already exist
    while (std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), countryName)!=Map::Instance().get_territories()->end()) {
        std::cout << "This country name is already taken. Pick another name: " << std::endl;
        std::cin >> countryName;
    }
    
    Map::Territory* newTerritory = new Map::Territory();
    newTerritory->set_name(countryName);
    Map::Instance().get_territories()->push_back(newTerritory);
    
    
}

// Method called when the user wants to define the adjacency between 2 countries
// Load .map and browse to search for the name of these 2 countries and ask to be adjacent or not
// If one or two of the country not found, error message
void  Map::AdjacencyDefiner() {
    int answer;
    std::string firstCountry, secondCountry;
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
    Map::Territory* aTerritory = new Map::Territory;
    Map::Territory* anotherTerritory = new Map::Territory;
    // **Problem here**: std::find returns an iterator, but must be cast to Object itself, may be done by dereferencing the iterator pointer but could not find a way to do so
    //aTerritory = std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), firstCountry);
    //anotherTerritory = std::find(Map::Instance().get_territories()->begin(), Map::Instance().get_territories()->end(), secondCountry);
    // If they are adjacent
    if (aTerritory->AreAdjacent(anotherTerritory)) {
        std::cout << "These 2 territories are adjacent." << std::endl;
        std::cout << "Make them nonadjacent? (1 for yes/0 for no)" << std::endl;
        std::cin >> answer;
        if (answer==1) {
            // Removes each from other's adjacency list
            aTerritory->get_adjacency_list()->erase(std::find(aTerritory->get_adjacency_list()->begin(),aTerritory->get_adjacency_list()->end(),secondCountry));
            anotherTerritory->get_adjacency_list()->erase(std::find(anotherTerritory->get_adjacency_list()->begin(),anotherTerritory->get_adjacency_list()->end(),firstCountry));
        }
        
    }
    // If they are not adjacent
    else {
        std::cout << "These 2 territories are nonadjacent." << std::endl;
        std::cout << "Make them adjacent? (1 for yes/0 for no)" << std::endl;
        std::cin >> answer;
        if(answer==1) {
            // Add each country to the other's adjacency list
            //aTerritory->get_adjacency_list()->push_back(secondCountry);
            //anotherTerritory->get_adjacency_list()->push_back(firstCountry);
            
        }
    }
    
}

// Method called when the user wants to create a new continent
void  Map::ContinentCreator() {
    std::string continentName;
    std::cout << "Name of the Continent: " << std::endl;
    std::cin >> continentName;
    // Iterates to see if continent already exist
    while (std::find(Map::Instance().get_continents()->begin(), Map::Instance().get_continents()->end(), continentName)!=Map::Instance().get_continents()->end()) {
        std::cout << "This continent name is already taken. Pick another name: " << std::endl;
        std::cin >> continentName;
    }
    
    Map::Continent* newContinent = new Map::Continent();
    newContinent->set_name(continentName);
    Map::Instance().get_continents()->push_back(newContinent);
    
    
}
//--End of Map Editor--*/
