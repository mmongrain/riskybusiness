#include <boost/algorithm/string.hpp>
#include "game_in_progress_builder.h"
#include "continent.h"
#include "player.h"
#include "game.h"
#include "human_player.h"
#include "card.h"

void GameInProgressBuilder::BuildPlayerState(std::vector<std::string> section_players){

	// separating each player's string into tokens
	std::vector<Player*> *players = new std::vector < Player* > ;
	for (unsigned int i = 1; i < section_players.size(); ++i){
		std::vector<std::string> player_info;
		std::stringstream input(section_players[i]);
		std::string token;
		while (getline(input, token, ',')) {
			boost::trim(token);
			player_info.push_back(token);
		}

		// making the right kind of player (human or comp)
		Player *temp;
		if (player_info[0] == "HumanPlayer")
			temp = new HumanPlayer();
		else if (player_info[0] == "CompPlayer")
			temp = new CompPlayer();
		else
			std::cout << "Can't tell what kind of player it is!" << std::endl;

		// assign his player id
		temp->set_id(std::stoi(player_info[1]));

		// give him his cards
		std::deque<Card*> hand = temp->get_hand();
		for (unsigned int j = 2; j < player_info.size(); ++j){
			Card *c = new Card();
			c->set_type(player_info[j]);
			hand.push_back(c);
		}
	}
	Game::Instance().set_players(players);
}

void GameInProgressBuilder::BuildMapState(std::vector<std::string> section_continents, std::vector<std::string> section_territories){
	
	// building continents
	Map::Instance().ParseMapInfo(section_continents);

	// building territories
	for (unsigned int i = 0; i < section_territories.size(); i++) {

		Territory *temp = new Territory;
		std::vector<std::string> territory;
		std::stringstream input(section_territories[i]);
		std::string token;
		while (getline(input, token, ',')) {
			boost::trim(token);
			territory.push_back(token);
		}
		temp->set_name(territory[0]);
		temp->set_x(std::stoi(territory[1]));
		temp->set_y(std::stoi(territory[2]));

		// find the continent it belongs to
		std::vector<Continent*> *continents = Map::Instance().get_continents();
		for (unsigned int j = 0; j < continents->size(); j++) {
			if (boost::iequals((*continents)[j]->get_name(), territory[3])) {
				temp->set_continent((*continents)[j]);
				(*continents)[j]->get_territories().push_back(temp);
			}
		}
		if (temp->get_continent() == NULL) {
			std::cout << "Error in ParseTerritoryInfo: Continent not found for "
				<< temp->get_name() << std::endl;
		}
		for (unsigned int j = 4; j < territory.size()-2; j++) {
			Territory *terr = new Territory();
			terr->set_name(territory[j]);
			boost::trim(terr->get_name());
			std::vector<Territory*> *adj_list = temp->get_adjacency_list();
			adj_list->push_back(terr);
		}

		// find the player it belongs to
		int player = atoi(territory[territory.size() - 2].c_str()); // cast string to integer
		std::vector<Player*> *players = Game::Instance().get_players();

		
		for (unsigned int k = 0; k < players->size(); ++k){
			if ((*players)[k]->get_id() == player){
				// add it to the player's territories
				(*players)[k]->get_owned_territories().push_back(temp);

				// make him the territory's owner
				temp->set_owner((*players)[k]);
				break;
			}
		}

		// Set number of units
		temp->set_num_units(territory.size() - 1);
		Map::Instance().get_territories()->push_back(temp);
	}
}

void GameInProgressBuilder::BuildGameState(std::vector<std::string> section_gamestate){

	// Current player
	std::size_t delim = section_gamestate[1].find("1");
	int current_player_id = std::stoi(section_gamestate[1].substr(delim + 1));
	std::vector<Player*> *players = Game::Instance().get_players();
	Player *current_player;
	// finding which player has the index specified in the log file
	for (unsigned int i = 0; i < (*players).size(); ++i){
		if ((*players)[i]->get_id() == current_player_id){

			// set current player to the found player
			current_player = (*players)[i];
			Game::Instance().set_current_player(current_player);
			break;
		}
		std::cout << "Current player id not found! No current player assigned" << std::endl;
	}

	// Current turn phase
	std::size_t delim1 = section_gamestate[1].find("=");
	int current_phase = std::stoi(section_gamestate[1].substr(delim1 + 1));
	current_player->set_phase(current_phase);


}