#include <iostream>
#include <stdlib.h> // rand()
#include <string>
#include <vector>
#include <algorithm>

#include "card.h"
#include "comp_player.h"
#include "game.h"
#include "human_player.h"
#include "map.h"
#include "player.h"
#include "player_view.h"
#include "strategy.h"
#include "strategy_aggressive.h"
#include "strategy_defensive.h"
#include "strategy_random.h"
#include "territory.h"

void Game::PlayGame() {
	bool wantsToPlay = true;
	while (wantsToPlay) {
		Instance().PrintLogo();
		Instance().Startup();
		Instance().MainPhase();
		wantsToPlay = Instance().EndGame();
	}
}

void Game::TestHelper() {
	for (auto player : players) {
    player->set_battles_won(rand() % 100);
    player->set_battles_lost(rand() % 100);
    player->set_total_units(rand() % 256);
  }
}

void Game::TestHelper(int num_players) {
	Game::players = *(new std::vector<Player*>);
	for (int i = 0; i < num_players; i++){
		players.push_back(new HumanPlayer());
    players.back()->set_battles_won(rand() % 100);
    players.back()->set_battles_lost(rand() % 100);
    players.back()->set_total_units(rand() % 256);
    int num_cards = rand() % 6;
    for (int i = 0; i < num_cards; i++) {
      players.back()->add_card(new Card(Card::SOLDIER));
    }
	}
	AssignCountries();
}

void Game::Startup()
{
	std::cout << "\n===== STARTUP PHASE =====\n\n";

	// creating HumanPlayer objects
	std::cout << "Please enter a number of human players between 0 and 6:\n";
	std::cin >> num_human_players;
	while (num_human_players < 0 || num_human_players > 6)
	{
		std::cout << "Wrong input! Please enter a number of players between 0 and 6:\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin >> num_human_players;
	}

	Game::players = *(new std::vector<Player*>);
	for (int i = 0; i < num_human_players; i++) {
		players.push_back(new HumanPlayer());
    player_views.push_back(new PlayerView(players.back()));
	}

	// creating ComputerPlayer objects, to be re-done using exceptions
	if (num_human_players > 3) {
		std::cout << "Please enter a number of computer players between 0 and " << 6 - num_human_players << std::endl;
		// verify input
		while (!(std::cin >> num_comp_players) || num_comp_players < 0 || num_comp_players > 6 - num_human_players)
		{
			std::cout << "Wrong input! Please enter a number of computer players between 0 and "
				<< 6 - num_human_players << ":\n" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		if (num_comp_players != 0) {
			std::cout << num_comp_players << " Computer Players are being created..." << std::endl;
			CustomCompPlayers();
		}
	}
	else {
		// if more than 1 human player, can have 0 CompPlayers, otherwise make CompPlayer(s) to make sure we have 2 players total
		int min_comp_players = (num_human_players > 1) ? 0 : 2 - num_human_players;
		int max_comp_players = 6 - num_human_players;

		std::cout << "Please enter a number of computer players between " << min_comp_players << " and " << max_comp_players
			<< "\nor press " << max_comp_players + 1 << " and I will create one Computer player of each kind: "
			<< "Aggressive, Defensive and Random." << std::endl;

		// get and check input
		while (!(std::cin >> num_comp_players) || num_comp_players < min_comp_players || num_comp_players > max_comp_players + 1)
		{
			std::cout << "Wrong input! Please enter a number of computer players between " << min_comp_players << " and "
				<< max_comp_players << "\nor press " << max_comp_players + 1
				<< " and I will create one Computer player of each kind: " << "Aggressive, Defensive and Random." << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}

		// making default CompPlayers
		if (num_comp_players == max_comp_players + 1){
			std::cout << "Three default Computer Players are being created... " << std::endl;
			DefaultCompPlayers();
		}

		// making custom CompPlayers
		else {
			if (num_comp_players != 0){
				std::cout << num_comp_players << " custom Computer Players are being created..." << std::endl;
				CustomCompPlayers();
			}
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
    player_views.push_back(new PlayerView(players.back()));
	}
	for (int i = num_human_players; i < players.size(); i++){
		ApplyStrategyChoice(i % 3 + 1, (CompPlayer*)players[i]);
	}
}

// Lets the user choose a strategy for each CompPlayer
void Game::CustomCompPlayers(){
	for (int i = 0; i < num_comp_players; i++){
		players.push_back(new CompPlayer());
    player_views.push_back(new PlayerView(players.back()));
	}
	for (int i = num_human_players; i < players.size(); i++){
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
	std::vector<Territory*> territories = Map::Instance().get_copy_territories();
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
	std::vector<Territory*> terr = *(Map::Instance().get_territories());
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
	int turn = 1;
	std::cout << "\n===== MAIN PLAY PHASE =====" << std::endl;
	while (game_over == false) {
		std::cout << "--------- TURN #" << turn << ":---------";
		for (int i = 0; i < players.size(); i++) // round-robin loop over the players 
		{
			players[i]->PlayTurn();
			if (game_over)
				return;
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
		++turn;
	}
}

void Game::killPlayer(Player* deadPlayer){
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPLAYER " << deadPlayer->get_id()
		<< " IS DEAD!\nRIP\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
	players.erase(std::remove(players.begin(), players.end(), deadPlayer), players.end());
}

bool Game::EndGame(){
	Player* winner = players[0];
	std::cout << "\nPLAYER " << winner->get_id() << " WINS!"
		<< "\nThank you for playing.\nTo play again, press 1,\nTo savor your victory and rub it in people's faces, press 0" << std::endl;
	int answer;
	std::cin >> answer;
	while (answer != 0 && answer != 1)
	{
		std::cout << "Wrong input! Press 1 to start another game or 0 to stop playing" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin >> answer;		
	}
	if (answer == 1)
		return true;
	return false;
}

void Game::set_game_over(bool value){
	game_over = value;
}

bool Game::get_game_over(){
	return game_over;
}

void Game::PrintLogo() {
	std::cout << " ____  _     _\n|  _ \\(_)___| | ___   _\n| |_) | / __| |/ / | | |\n|  _ <| \\__ \\   <| |_| |\n|_|_\\_\\_|___/_|\\_\\\\__, |\n| __ ) _   _ ___(_)___/   ___  ___ ___\n|  _ \\| | | / __| | '_ \\ / _ \\/ __/ __|\n| |_) | |_| \\__ \\ | | | |  __/\\__ \\__ \\\n|____/ \\__,_|___/_|_| |_|\\___||___/___/" << std::endl;
}

