#include <string>
#include <iostream>

#include "unit-map.h"

int main() {
	// Change these values depending on what you want to test
	char filename[16] = "World.map";
	std::string territory = "Quebec";
	std::string continent = "Europe";

	// Run through the unit tests and print success to stdout
	UnitMap::Instance();
	std::cout << "UnitMap::Instance passed!" << std::endl;
	UnitMap::Load(filename);
	std::cout << "UnitMap::Load passed!" << std::endl;
	UnitMap::Save(filename);
	std::cout << "UnitMap::Save passed!" << std::endl;
	UnitMap::VerifyConnectivity(filename);
	std::cout << "UnitMap::VerifyConnectivity passed!" << std::endl;
	UnitMap::StringToTerritory(filename, territory);
	std::cout << "UnitMap::StringToTerritory passed!" << std::endl;
	UnitMap::StringToContinent(filename, continent);
	std::cout << "UnitMap::StringToContinent passed!" << std::endl;
	std::cout << "All tests passed--unit test successful." << std::endl;
}
