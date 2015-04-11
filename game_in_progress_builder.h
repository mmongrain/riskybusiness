#ifndef GAME_IN_PROGRESS_BUILDER_H_
#define GAME_IN_PROGRESS_BUILDER_H_
#include "game_builder.h"
#include <vector>

class GameInProgressBuilder : public GameBuilder {
	void BuildMapState(std::vector<std::string> section_continents, std::vector<std::string> section_territories);
	void BuildPlayerState(std::vector<std::string> section_players);
	void BuildGameState(std::vector<std::string> section_gamestate);
};

#endif