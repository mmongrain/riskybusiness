#include "Game.h"
#include "Player.h"
#include <iostream>

Game::Game()
{	
	game_over = false;
}

void Game::playGame()
{
	startup();
	mainPhase();

	std::cout << "\nGame over. GGWP!\n" << std::endl;
}

void Game::startup()
{
	std::cout << "===== STARTUP PHASE =====\n\n";
	std::cout << "Please enter a number of players between 2 and 6:\n";	

	// verify input
	while (!(std::cin >> numOfPlayers) || numOfPlayers < 2 || numOfPlayers > 6) 
	{	
		std::cout << "Wrong input! Please enter a number of players between 2 and 6:\n";
		std::cin.clear();
		std::cin.ignore (1000, '\n');
	}

	// creating player objects
	Game::players = new Player* [numOfPlayers];
	for (int i = 0; i < numOfPlayers; i++){
		players[i] = new Player(i+1);
	}	

	assignCountries();
}

void Game::assignCountries()
{
	std::cout << "Countries have been assigned" << std::endl;
}

void Game::mainPhase()
{
	std::cout << "\n===== MAIN PLAY PHASE =====\n";
	while (game_over == false)
	{
		for (int i = 0; i < numOfPlayers; i++) // round-robin loop over the players
		{
			players[i]->playTurn();
		}

		// END OF GAME
		// temporary way to end the game (to be replaced by actual conditions for ending the game)
		std::cout << "\n\nPress 1 to continue playing or 0 to stop" << std::endl;
		int answer;
		while (!(std::cin >> answer) || (answer != 0 && answer != 1)) 
		{	
		std::cout << "Wrong input! Press 1 to continue playing or 0 to stop" << std::endl;
		std::cin.clear();
		std::cin.ignore (1000, '\n');
		}
		if (answer == 0)
			game_over = true;
	}
}

Game::~Game()
{
	delete[] players;
	players = NULL;
}
