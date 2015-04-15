#include "map.h"
#include "territory.h"
#include "continent.h"
#include <string>
#include <iostream>

int main () {
	// DEMO MAIN FOR MAP METHODS
	// The Load and Save methods take c-style strings as parameters
	// Either you can explicitly declare an array of chars as below,
	// or use std::string.c_str() to convert std::strings to the
	// appropriate format.
	char filename[16] = "World.map";
	char file_out[16] = "test.map";

	// Map is a singleton class, so everything must be called thru
	// Instance(), as below. Don't try to instantiate a Map--it won't
	// work so much.

	// Load a map from disk
	Map::Instance().Load(filename);

	// Save it to a new file
	Map::Instance().Save(file_out);

	// Verify that it's connected
	Map::Instance().VerifyConnectivity();

	// Check to see if some territories or continents with certain 
	// names exist in the map and get them to do stuff
	std::string territory = "Quebec";
	std::string continent = "Africa";

	Territory* territory_pointer = Map::Instance().StringToTerritory(territory);
	Continent* continent_pointer = Map::Instance().StringToContinent(continent);

	std::cout << territory_pointer->get_name() << std::endl; // Should print territory
	std::cout << continent_pointer->get_name() << std::endl; // Should print continent
}