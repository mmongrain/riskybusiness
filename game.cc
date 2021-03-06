#include <iostream>
#include <fstream>
#include <stdlib.h> // rand()
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <SFML/System.hpp>

#include "card.h"
#include "deck.h"
#include "game.h"
#include "gui.h"
#include "player.h"
#include "strategy.h"
#include "random_ai_player.h"
#include "defensive_ai_player.h"
#include "aggressive_ai_player.h"
#include "map.h"
#include "player_view.h"
#include "stats_basic.h"
#include "stats_control.h"
#include "stats_battle.h"
#include "territory.h"
#include "map_editor.h"
#include "ui.h"

class Player;

void Game::PlayGame() {
  Instance().Startup();
  Instance().MainPhase();
  Instance().EndGame();
}

// ===== STARTUP PHASE =====

void Game::Startup() {

  // DEFAULT OPTIONS
  // "GUI" Mode launches a visual, noninteractive game board
  gui_mode = false;
  // Verbose Mode prints every update to anything to cout
  verbose_mode = false;
  // GUI Map Labels prints names of territories on the board
  gui_labels = true;
  // GUI Author Info prints the author information to the board
  gui_authorinfo = false;
  // Slow Mode slows the CPU down a little to make it less jarring for the human player
  slow_mode = true;
  // Gladiator mode pits history's greatest computers against each other in a battle to the death
  gladiator_mode = false;

  turn = 1;

  MainMenu();
  LoadMap();  
  // Initialize the Deck of cards. Must be done after the map is loaded.
  Deck::Instance().Generate(*(Map::Instance().get_territories()));   
  CreatePlayers();
  AssignCountries();
  if (gui_mode) { 
    std::thread logic_thread(&Game::GUIHelper);
    GUI::RevengeOfTheGUI();
  }
}

void Game::GUIHelper() {
  Instance().MainPhase();
  Instance().EndGame();
}

// Load a mapfile selected by user
void Game::LoadMap() {
  UI::ClearBuffer();
  for (;;) {
    char filename[100];
    UI::GetMapfile(filename);
    std::ifstream file(filename);
    if (file.good()) {
      file.close();
      if (Map::Instance().Load(filename)) {
        if (Map::Instance().VerifyConnectivity()) {
          UI::StatusMessage("Map loaded successfully!");
          break;
        }
      }     
    }
    UI::StatusMessage("Mapfile not found or is invalid! Check to make sure the .map file is in the current directory and that it is in a valid format.");
    file.close();
  }
}

// Creating a number of Player objects chosen by user
void Game::CreatePlayers() {

  int num_humans = 0;
  int num_robots = 0;
  int difficulty = 0;

  if (gladiator_mode) {
	  num_robots = 6;
	  difficulty = 3;

  } else if (UI::SingleOrMulti()) {
    num_humans = UI::GetNumPlayers(2, 6);
    num_robots = UI::GetNumAIPlayers(0, 6 - num_humans);
    if (num_robots) { 
      difficulty = UI::GetDifficulty(); 
    }

  } else {
    num_humans = 1;
    num_robots = UI::GetNumAIPlayers(1, 5);
    difficulty = UI::GetDifficulty();
  }

  Game::players = *(new std::vector<Player*>);
  UI::player_views = *(new std::vector<PlayerView*>);
  for (int i = 0; i < num_humans; i++) {
    players.push_back(new Player());
    UI::player_views.push_back(new PlayerView(players.back()));
  }

  std::vector<std::string> ai_names {
    "Commodore 64",
    "UNIVAC",
    "Watson",
    "HAL 9000",
    "Manchester Mark 1",
    "Apple ]["
  };
  std::random_shuffle(ai_names.begin(), ai_names.end());


  for (int i = 0; i < num_robots; i++) {
    players.push_back(new Player());
    int ai_type = difficulty;
    if (difficulty == 3) {
      ai_type = i % 3;
    }
    switch (ai_type) {
      case 0: players.back()->set_strategy(new Random());
              break;
      case 1: players.back()->set_strategy(new Defensive());
              break;
      case 2: players.back()->set_strategy(new Aggressive());
              break;
    }
    players.back()->set_name(ai_names.back());
    ai_names.pop_back();
    UI::player_views.push_back(new PlayerView(players.back()));
  } 

  UI::stats = new StatsBasic;
  UI::stats = new StatsControl(UI::stats);
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
  UI::StatusMessage("Countries have been assigned randomly!");
}

// ===== MAIN GAME PHASE : round-robin loop for players� turns =====
// Game phases are implemented in the Player class

void Game::MainPhase()
{
  while (game_over == false) {
    for (unsigned int i = 0; i < players.size(); i++)
    {
      UI::StartTurn(turn, players[i]);
      players[i]->PlayTurn();
      if (game_over)
        return;
    }
    ++turn;
  }
}

// ===== WINNING THE GAME =====

void Game::EndGame(){
  Player* winner = players[0];
  UI::EndGame(winner);
}

// ===== OTHER GAME METHODS =====

// Main Menu loop
void Game::MainMenu(){
  UI::PrintLogo();
  for (;;) {
    std::vector<std::string> options{
      "Play Game",      // 0
      "Map Editor",     // 1
      "Game Options",   // 2
      "Help",           // 3 
      "About This Game" // 4
    };
    int option = UI::StringMenu("MAIN MENU", options);
    if (option == 0) break;
	  if (option == 1) { MapEditor::StartMapEditor(); }
    if (option == 2) { Options(); }
    if (option == 3) { UI::MainHelp(); }
    if (option == 4) { UI::About(); }
  }
}

void Game::KillPlayer(Player* dead_player) {
  UI::KillPlayer(dead_player);
  players.erase(std::remove(players.begin(), players.end(), dead_player), players.end());
}

void Game::Options() {
  for (;;) {
    std::string gui_on = gui_mode ? "[ON]" : "[OFF]";
    std::string verbose_on = verbose_mode ? " [ON]" : "[OFF]";
    std::string gui_labels_on = gui_labels ? "[ON]" : "[OFF]";
    std::string gui_authorinfo_on = gui_authorinfo ? "[ON]" : "[OFF]";
	  std::string gladiator_mode_on = gladiator_mode ? "[ON]" : "[OFF]";
    std::string slow_mode_on = slow_mode ? "[ON]" : "[OFF]";
    std::vector<std::string> options {
      "Return to main menu",
      "\"GUI\" mode " + gui_on,
      "Verbose mode " + verbose_on,
      "GUI Map labels " + gui_labels_on,
      "GUI Author Info " + gui_authorinfo_on,
	    "Gladiator Mode " + gladiator_mode_on,
      "Slow Mode " + slow_mode_on
    };
    int option = UI::StringMenu("OPTIONS MENU", options);
    switch (option) {
    case 0: return;
    case 1: gui_mode = !gui_mode;
      break;
    case 2: verbose_mode = !verbose_mode;
      break;
    case 3: gui_labels = !gui_labels;
      break;
    case 4: gui_authorinfo = !gui_authorinfo;
      break;
	  case 5: gladiator_mode = !gladiator_mode;
	     break;
    case 6: slow_mode = !slow_mode;
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
// Leaving these here for the potential benefit of the other teams' unit testers :)

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
    players.push_back(new Player());
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
