#include "game.h"
#include "player.h"
#include "human_player.h"
#include "map.h"
#include <iostream>
#include <stdlib.h> // rand()
#include <string>
#include <vector>
#include <algorithm>

Game::Game() {
	game_over = false;
}

void Game::PlayGame() {
	Startup();
	MainPhase();

	std::cout << "\nGame over. GGWP!\n" << std::endl;
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
		players[i] = new HumanPlayer();
	}

	// creating ComputerPlayer objects
	if (num_human_players < 6) {
		std::cout << "Please enter a number of computer players between 2 and " << 6 - num_human_players 
			<< ":\n (So there will be at most 6 players)"<< std::endl;
		// verify input
		while (!(std::cin >> num_comp_players) || num_comp_players < 0 || num_comp_players > 6 - num_human_players)
		{
			std::cout << "Wrong input! Please enter a number of computer players between 0 and "
				<< 6 - num_human_players << ":\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
	}
	AssignCountries();
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
}

void Game::MainPhase()
{
	std::cout << "\n===== MAIN PLAY PHASE =====\n";
	while (game_over == false) {
		for (int i = 0; i < num_human_players; i++) // round-robin loop over the players 
    {
			players[i]->PlayTurn();
		}

		// END OF GAME
		// temporary way to end the game (to be replaced by actual conditions for ending the game)
		std::cout << "\n\nPress 1 to continue playing or 0 to stop" << std::endl;
		int answer;
		while (!(std::cin >> answer) || (answer != 0 && answer != 1))
		{
			std::cout << "Wrong input! Press 1 to continue playing or 0 to stop" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		if (answer == 0)
			game_over = true;
	}
}

Game::~Game()
{
  std::vector<Player*> *player_point = &players;
	delete player_point;
	player_point = 0;
}
