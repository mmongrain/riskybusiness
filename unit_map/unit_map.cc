void UnitMap::Instance() {
	Map map1 = Map::Instance();
	Map map2 = Map::Instance();
	assert (&map1 == &map2);
}

void UnitMap::Load(char* filename) {
	Map::Instance().Load(filename);
	assert( continents.size != 0 &&
		    territories.size != 0 &&
		    VerifyConnectivity()
	);
}

void UnitMap::Save(char* filename) {
	Map::Instance().Load(filename);
	std::vector<Territory*> loaded_territories = territories;
	std::vector<Continents*> loaded_continents = continents;
	char test_out[100] = "test_out.map";
	Map::Instance().Save(test_out);
	Map::Instance().Load(test_out);
	std::vector<Territory*> saved_territories = territories;
	std::vector<Continents*> saved_continents = continents;
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
			assert(Map::Instance().StringToTerritory(s) == continents[i]);
		}
	}
}