#include <iostream>
#include <fstream>
#include <stdlib.h> // rand()
#include <string>
#include <vector>
#include <algorithm>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "human_player.h"
#include "map.h"
#include "player_view.h"
#include "stats_basic.h"
#include "stats_control.h"
#include "stats_battle.h"
//#include "comp_player.h"
//#include "strategy.h"
//#include "strategy_aggressive.h"
//#include "strategy_defensive.h"
//#include "strategy_random.h"
#include "ui.h"

class Player;
class Territory;

void Game::PlayGame() {
  bool wantsToPlay = true;
  while (wantsToPlay) {
    UI::PrintLogo();
    Instance().Startup();
    Instance().MainPhase();
    wantsToPlay = Instance().EndGame();
  }
}

// ===== STARTUP PHASE =====

void Game::Startup() {
  gui_mode = false;
  verbose_mode = false; 

  MainMenu();
  LoadMap();  
  Deck::Instance().Generate();  // Initialize the Deck of cards. Must be done after the map is loaded.
  CreatePlayers();
  AssignCountries();
}

// Load a mapfile selected by user
void Game::LoadMap(){
	for (;;) {
		char filename[100];
		UI::GetMapfile(filename);
		std::ifstream file(filename);
		if (file.good()) {
			file.close();
			Map::Instance().Load(filename);
			break;
		}
		UI::StatusMessage("Mapfile not found! Check to make sure the .map file is in the current directory.");
		file.close();
	}
}

// Creating a number of Player objects chosen by user
void Game::CreatePlayers(){
	int num_players = UI::GetNumPlayers(2, 6);
	UI::player_views = *(new std::vector<PlayerView*>);
	Game::players = *(new std::vector<Player*>);
	for (int i = 0; i < num_players; i++) {
		players.push_back(new HumanPlayer());
		UI::player_views.push_back(new PlayerView(players.back()));
	}
	UI::stats = new StatsBasic;
	UI::stats = new StatsControl(UI::stats);
	UI::stats = new StatsBattle(UI::stats);
}

// Randomly assigning countries
void Game::AssignCountries() {
	// Get a copy of the territories
	std::vector<Territory*> territories = Map::Instance().get_copy_territories();
	// For each territory
	for (unsigned int i = 0; territories.size() > 0; i++) {
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
	// PrintOwnershipInfo(); // used for testing
}

// ===== MAIN GAME PHASE : round-robin loop for players’ turns =====
// Game phases are implemented in the Player class

void Game::MainPhase()
{
	int turn = 1;
	std::cout << "\n===== MAIN PLAY PHASE =====" << std::endl;
	while (game_over == false) {
		std::cout << "--------- TURN #" << turn << ":---------";
		for (unsigned int i = 0; i < players.size(); i++)
		{
			players[i]->PlayTurn();
			if (game_over)
				return;
		}
		++turn;
		EndOfTurn();	
	}
}

// ===== WINNING THE GAME =====

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

// ===== OTHER GAME METHODS =====

// Main Menu loop
void Game::MainMenu(){
	for (;;) {
		std::vector<std::string> options{
			"Play Game",      // 0
			"Map Editor",     // 1
			"Game Options"    // 2
		};
		int option = UI::StringMenu("MAIN MENU", options);
		if (option == 0) break;
		if (option == 1) {} // MapEditor goes here
		if (option == 2) { Options(); }
	}
}

void Game::KillPlayer(Player* deadPlayer){
	std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nPLAYER " << deadPlayer->get_id()
		<< " IS DEAD!\nRIP\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
	players.erase(std::remove(players.begin(), players.end(), deadPlayer), players.end());
}

// stops after each turn (useful with CompPlayers)
void Game::EndOfTurn(){
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

void Game::Options() {
	for (;;) {
		std::string gui_on = gui_mode ? "[ON]" : "[OFF]";
		std::string verbose_on = verbose_mode ? "[ON]" : "[OFF]";
		std::vector<std::string> options{
			"Return to main menu",
			"\"GUI\" mode " + gui_on,
			"Verbose mode " + verbose_on,
		};
		int option = UI::StringMenu("OPTIONS MENU", options);
		switch (option) {
		case 0: return;
		case 1: gui_mode = !gui_mode;
			break;
		case 2: verbose_mode = !verbose_mode;
			break;
		}
	}
}

void Game::set_game_over(bool value){
	game_over = value;
}

bool Game::get_game_over(){
	return game_over;
}

// METHODS FOR TESTING

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

void Game::PrintOwnershipInfo(){
	std::vector<Territory*> terr = *(Map::Instance().get_territories());
	for (unsigned int i = 0; i < terr.size(); i++){
		std::cout << terr[i]->get_name() << ": Player " << terr[i]->get_owner()->get_id() << std::endl;
	}

	for (unsigned int i = 0; i < players.size(); ++i){
		std::cout << "Player " << players[i]->get_id() << ": " << std::endl;
		players[i]->PrintOwnedTerritories();
	}
}

/* Makes one CompPlayer of each kind (aggressive, defensive, random)
void Game::DefaultCompPlayers(){
  for (unsigned int i = 0; i < 3; i++){
    players.push_back(new CompPlayer());
    player_views.push_back(new PlayerView(players.back()));
  }
  for (unsigned int i = num_human_players; i < players.size(); i++){
    ApplyStrategyChoice(i % 3 + 1, (CompPlayer*)players[i]);
  }
}

// Lets the user choose a strategy for each CompPlayer
void Game::CustomCompPlayers(){
  for (int i = 0; i < num_comp_players; i++){
    players.push_back(new CompPlayer());
    player_views.push_back(new PlayerView(players.back()));
  }
  for (unsigned int i = num_human_players; i < players.size(); i++){
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
}*/
