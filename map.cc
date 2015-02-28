
#include "map.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "player.h"

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
		else
    return true;
	}
}

void Map::Territory::PrintAdjacentTerritories() {
  for (int i = 0; i < adjacency_list.size(); i++) {
    std::cout << adjacency_list[i]->get_name() << " (" 
              << adjacency_list[i]->get_num_units() << ", Player " 
              << adjacency_list[i]->get_owner()->get_id() << ")";
    (i < adjacency_list.size() - 1) ? std::cout << ", " : std::cout << ".\n";
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

void Map::ParseMapInfo(const std::vector<std::string> &section_map) {
  for (unsigned int i = 0; i < section_map.size(); i++) {
    /* TODO: Fix the clearing for all three Parse methods
     * right now the clear is happening at the end of method execution,
     * which obviously borks everything, idk why
     * Clear out the existing struct
    map_info.author = "";
    map_info.image = "";
    map_info.wrap = true;
    map_info.scroll = 'n';
    map_info.warn = true; */
    std::size_t delim = section_map[i].find("=");
    /**
     * XXX: Possible portability problem 
     * For some reason each line on my system is followed by two invisible
     * characters that badly bork the strings. (This might be a feature of
     * Windows-formatted files). -2 is a magic number, and may be different on 
     * your system. 
     * TODO: Find out what's actually going on
     */
    int end_of_string = section_map[i].length() - delim - 2;
    std::string field = section_map[i].substr(0, delim);
    std::string value = section_map[i].substr(delim + 1, end_of_string); 

    // Convert field to an enum when you get the chance
    if (field.compare("author") == 0) { // "If strings are identical" 
      map_info.author = value;

    } else if (field.compare("image") == 0) {
      map_info.image = value;

    } else if (field.compare("wrap") == 0) {
      map_info.wrap = (value.compare("yes") == 0);
    
    } else if (field.compare("scroll") == 0) {
      if (value.compare("horizontal") == 0) {
        map_info.scroll = 'h';
      } else if (value.compare("vertical") == 0) {
        map_info.scroll = 'v';
      } else {
        map_info.scroll = 'n';
      }

    } else if (field.compare("warn") == 0) {
      map_info.warn = (value.compare("yes") == 0);
    }
  }
}

void Map::ParseContinentInfo(const std::vector<std::string> &section_continents) {
  for (unsigned int i = 0; i < section_continents.size(); i++) {
    // continents.clear();
    std::size_t delim = section_continents[i].find("=");
    Continent *continent = new Continent;
    continent->name = section_continents[i].substr(0, delim);
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
      token = token.substr(0, token.length());
      territory.push_back(token);
    }

    // Eats the EOF character, which breaks everything
    int last = territory.size() - 1;
    territory[last] = territory[last].substr(0, territory[last].length() - 1);

    // Write to the territory struct and add it to the master territories list
    temp->name = territory[0];
    temp->x = std::stoi(territory[1]);
    temp->y = std::stoi(territory[2]);

    // Find the continent it belongs to
    for (int j = 0; j < continents.size(); j++) {
      if (continents[j]->get_name().compare(territory[3]) == 0) {
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
