#include "game.h"
#include "player.h"
#include "comp_player.h"
#include "human_player.h"
#include "map.h"
#include <iostream>
#include <stdlib.h> // rand()
#include <string>
#include <vector>
#include <algorithm>
#include "strategy.h"
#include "strategy_aggressive.h"
#include "strategy_defensive.h"
#include "strategy_random.h"

void Game::PlayGame() {
	Startup();
	MainPhase();

	std::cout << "\nGame over. GGWP!\n" << std::endl;
}

void Game::PlayerViewTestHelper(int num_players) {
	Game::players = *(new std::vector<Player*>);
	for (int i = 0; i < num_players; i++){
		players.push_back(new HumanPlayer());
	}
	AssignCountries();
}

void Game::Startup()
{
	std::cout << "===== STARTUP PHASE =====\n\n";

	// creating HumanPlayer objects
	std::cout << "Please enter a number of human players between 2 and 6:\n";
	while (!(std::cin >> num_human_players) || num_human_players < 2 || num_human_players > 6)
	{
		std::cout << "Wrong input! Please enter a number of players between 2 and 6:\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	Game::players = *(new std::vector<Player*>);
	for (int i = 0; i < num_human_players; i++){
		players.push_back(new HumanPlayer());
	}

	// creating ComputerPlayer objects, this long thing can be simplified a bit I think..
	if (num_human_players > 3) {
		std::cout << "Please enter a number of computer players between 0 and " << 6 - num_human_players
			<< ":\n (So there will be at most 6 players)" << std::endl;
		// verify input
		while (!(std::cin >> num_comp_players) || num_comp_players < 0 || num_comp_players > 6 - num_human_players)
		{
			std::cout << "Wrong input! Please enter a number of computer players between 0 and "
				<< 6 - num_human_players << ":\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		std::cout << num_comp_players << "Computer Players are being created..." << std::endl;
		CustomCompPlayers();
	}
	else {
		std::cout << "Please enter a number of computer players between 2 and 6 "
			<< "\nor press any other key and I will create one Computer player of each kind: "
			<< "\nAggressive, Defensive and Random." << std::endl;
		Game::players = *(new std::vector<Player*>);

		// making default CompPlayers
		if (!(std::cin >> num_comp_players) || num_comp_players < 2 || num_comp_players > 6)
		{
			std::cout << "Three default Computer Players are being created... " << std::endl;
			DefaultCompPlayers();
		}

		// making custom CompPlayers
		else {
			std::cout << num_comp_players << " custom Computer Players are being created..." << std::endl;
			CustomCompPlayers();
		}
	}
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	AssignCountries();
}

// Makes one CompPlayer of each kind (aggressive, defensive, random)
void Game::DefaultCompPlayers(){
	for (int i = 0; i < 3; i++){
		players.push_back(new CompPlayer());
	}
	for (int i = 0; i < players.size(); i++){
		ApplyStrategyChoice(i + 1, (CompPlayer*)players[i]);
	}
}

// Lets the user choose a strategy for each CompPlayer
void Game::CustomCompPlayers(){
	for (int i = 0; i < num_comp_players; i++){
		players.push_back(new CompPlayer());
	}
	for (int i = 0; i < players.size(); i++){
		int choice = 1;
		std::cout << "Choose desired strategy for Computer Player " << players[i]->get_id()
			<< ": \nAggressive(1)\nDefensive(2)\nRandom(3)" << std::endl;
		while (!(std::cin >> choice) || choice < 1 || choice > 3)
		{
			std::cout << "Wrong input! Please choose a strategy for Computer Player " << players[i]->get_id()
				<< " between the following options:\nAggressive(1)\nDefensive(2)\nRandom(3)" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		ApplyStrategyChoice(choice, (CompPlayer*)players[i]);
	}
}

// Translates the user's input integer into the corresponding strategy
void Game::ApplyStrategyChoice(int choice, CompPlayer* player){
	switch (choice){
	case 1:
		player->set_strategy(new Aggressive());
		std::cout << "Strategy of Computer Player " << player->get_id() << " has been set to Aggressive" << std::endl;
		break;
	case 2:
		player->set_strategy(new Defensive());
		std::cout << "Strategy of Computer Player " << player->get_id() << " has been set to Defensive" << std::endl;
		break;
	case 3:
		player->set_strategy(new Random());
		std::cout << "Strategy of Computer Player " << player->get_id() << " has been set to Random" << std::endl;
		break;
	default:
		std::cout << "Invalid strategy choice!" << std::endl;
	}
}

void Game::AssignCountries() {
	// Get a copy of the territories
	std::vector<Map::Territory*> territories = Map::Instance().get_copy_territories();
	// For each territory
	for (int i = 0; territories.size() > 0; i++) {
		// Random number between 0 and the size of territories
		int rando = rand() % territories.size();
		// Iterates thru the players using the index
		Player *current_player = players[i % players.size()];
		// Add that random territory to that player
		current_player->add_territory(territories[rando]);
		// Assign it to the player
		territories[rando]->set_owner(current_player);
		// Give it one unit
		territories[rando]->set_num_units(1);
		// Remove it from the territories vector, rinse, repeat
		territories.erase(std::remove(territories.begin(), territories.end(), territories[rando]), territories.end());
	}
	std::cout << "Countries have been assigned randomly!" << std::endl;

	// used for testing
	/*
	std::vector<Map::Territory*> terr = *(Map::Instance().get_territories());
	for (int i = 0; i < terr.size(); i++){
	std::cout << terr[i]->get_name() << ": Player " << terr[i]->get_owner()->get_id() << std::endl;
	}

	for (int i = 0; i < players.size(); ++i){
	std::cout << "Player " << players[i]->get_id() << ": " << std::endl;
	players[i]->PrintOwnedTerritories();
	}
	*/
}

void Game::MainPhase()
{
	std::cout << "\n===== MAIN PLAY PHASE =====";
	while (game_over == false) {
		for (int i = 0; i < num_human_players; i++) // round-robin loop over the players 
		{
			players[i]->PlayTurn();
		}

		// END OF GAME
		// temporary way to end the game (to be replaced by actual conditions for ending the game)
		std::cout << "\n\nPress 1 to continue playing or 0 to stop" << std::endl;
		int answer;
		std::cin >> answer;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		while (answer != 0 && answer != 1)
		{
			std::cout << "Wrong input! Press 1 to continue playing or 0 to stop" << std::endl;
			std::cin >> answer;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		if (answer == 0)
			game_over = true;
	}
}

