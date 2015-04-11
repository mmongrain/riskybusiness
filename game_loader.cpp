#include "game_loader.h"
#include <boost/algorithm/string.hpp>
#include "game_builder.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <string>


void GameLoader::set_game_builder(GameBuilder* my_builder){
	builder = my_builder;
}

void GameLoader::build_game(char* filename){
	std::ifstream file(filename);
	std::vector<std::string> section_players;
	std::vector<std::string> section_continents;
	std::vector<std::string> section_territories;
	std::vector<std::string> section_gamestate;
	std::string input;

	// Bad attempts at reusing Matt's code below


	// Eat any blank lines before [Players], ensure [Players] exists, eat [Players]:
	while (getline(file, input) && input.find("[Players]") == std::string::npos);

	// Read the contents of [Players] to a vector, eat [Continents];
	while (getline(file, input) && input.find("[Continents]") == std::string::npos) {
		if (input.length() >= 1) {
			section_players.push_back(input);
		}
	}

	// Read the contents of [Continents] to a vector, eat [Territories] 
	while (getline(file, input) && input.find("[Territories]") == std::string::npos) {
		if (input.length() >= 3) {
			section_continents.push_back(input);
		}
	}

	// Read the contents of [Territories] to a vector, eat [GameState] 
	while (getline(file, input) && input.find("[GameState]") == std::string::npos) {
		if (input.length() >= 9) { 
			section_territories.push_back(input);
		}
	}
	
	// Read the contents of [GameState] to a vector
	while (getline(file, input)) {
		if (input.length() >= 3) {
			section_gamestate.push_back(input);
		}
	}

	builder->BuildPlayerState(section_players);
	builder->BuildMapState(section_continents, section_territories);	
	builder->BuildGameState(section_gamestate);
}