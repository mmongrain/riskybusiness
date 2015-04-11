#ifndef GAME_BUILDER_H_
#define GAME_BUILDER_H_
#include <vector>

class GameBuilder{
public:
	virtual void BuildPlayerState(std::vector<std::string> section_players) = 0;
	virtual void BuildMapState(std::vector<std::string> section_continents, std::vector<std::string> section_territories) = 0;
	virtual void BuildGameState(std::vector<std::string> section_gamestate) = 0;

};

#endif