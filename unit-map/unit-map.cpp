#include <vector>
#include <string>
#include <cassert>

#include "unit-map.h"
#include "territory.h"
#include "continent.h"

void UnitMap::Instance() {
	Map* map1 = &Map::Instance();
	Map* map2 = &Map::Instance();
	assert (map1 == map2);
}

void UnitMap::Load(char* filename) {
	Map::Instance().Load(filename);
	assert( Map::Instance().get_continents()->size() != 0 &&
		    Map::Instance().get_territories()->size() != 0 &&
		    Map::Instance().VerifyConnectivity()
	);
}

void UnitMap::Save(char* filename) {
	Map::Instance().Load(filename);
	std::vector<Territory*> loaded_territories = *(Map::Instance().get_territories());
	std::vector<Continent*> loaded_continents = *(Map::Instance().get_continents());
	char test_out[100] = "test_out.map";
	Map::Instance().Save(test_out);
	Map::Instance().Load(test_out);
	std::vector<Territory*> saved_territories = *(Map::Instance().get_territories());
	std::vector<Continent*> saved_continents = *(Map::Instance().get_continents());
	assert (saved_territories.size() == loaded_territories.size() &&
		    saved_continents.size() == saved_continents.size() 
	);
}

// A connected map passed as the parameter will pass the assertion, an unconnected one will not
void UnitMap::VerifyConnectivity(char* filename) {
	Map::Instance().Load(filename);
	assert( Map::Instance().VerifyConnectivity() );
}

// If there is a territory with its name == s in the vector, assertion will pass, else nothing happens
void UnitMap::StringToTerritory(char* filename, std::string s) {
	Map::Instance().Load(filename);
	std::vector<Territory*> territories = *(Map::Instance().get_territories()); 
	for (unsigned int i = 0; i < territories.size(); i++) {
		if (territories[i]->get_name() == s) {
			assert(Map::Instance().StringToTerritory(s) == territories[i]);
		}
	}
}

// If there is a continent with its name == s in the vector, assertion will pass, else nothing happens
void UnitMap::StringToContinent(char* filename, std::string s) {
	Map::Instance().Load(filename);
	std::vector<Continent*> continents = *(Map::Instance().get_continents()); 
	for (unsigned int i = 0; i < continents.size(); i++) {
		if (continents[i]->get_name() == s) {
			assert(Map::Instance().StringToContinent(s) == continents[i]);
		}
	}
}

std::string Territory::ToString() {
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

std::string Continent::ToString() {
  std::string out = "";
  out = get_name() + "=" + std::to_string(get_bonus());
  return out;
}