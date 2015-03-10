#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

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
