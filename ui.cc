#include <exception>
#include <iostream>
#include <vector>
#include <string>

#include "card.h"
#include "player.h"
#include "territory.h"
#include "ui.h"

class Player;

Territory* UI::GetReinforceableTerritory (Player* player) {
  std::vector<Territory*> territories = player->get_owned_territories();
  int reinforcements = player->get_reinforcements();
  std::cout << "You have " << std::to_string(reinforcements) << " reinforcements."
        << "\nWhich territory would you like to reinforce? " << std::endl;
  return TerritoryMenu(territories);
}

void UI::StatusMessage(std::string message) {
  std::cout << message << std::endl;
}

Territory* UI::TerritoryMenu(std::vector<Territory*> territories) {
  char menu_option = 'a';
  char input = '*';
  for (unsigned int i = 0; i < territories.size(); i++) {
    std::cout << menu_option << ") " << territories[i]->get_name() << std::endl;
    if (menu_option == 'z') { menu_option = 'A'; }
    else { ++menu_option; }
  }
  // "while input is invalid"
  while (MenuChoice(menu_option, input) == -1) {
    std::cin >> input;
    if (input == '?') {
      char help = HelpMenu();
    }
  }
  int choice = MenuChoice(menu_option, input);
  std::cout << std::endl;
  return territories[choice];
}

int UI::StringMenu(std::string title, std::vector<std::string> options) {
  std::cout << "-==" << title << "==-" << std::endl;
  char menu_option = 'a';
  char input = '*';
  for (unsigned int i = 0; i < options.size(); i++) {
    std::cout << menu_option << ") " << options[i] << std::endl;
    if (menu_option == 'z') { menu_option = 'A'; }
    else { ++menu_option; }
  }
  // "while input is invalid"
  while (MenuChoice(menu_option, input) == -1) {
    std::cin >> input;
    if (input == '?') {
      char help = HelpMenu();
    }
  }
  std::cout << std::endl;
  return MenuChoice(menu_option, input);
}

// menu_option is the character after the highest acceptable value
// returns -1 on error, index otherwise
int UI::MenuChoice(char menu_option, char input) {
  // Nonalphabetical characters are default invalid (caps territories at 52, which is probably fine)
  // beyond that a GUI would really be necessary anyway
  if (input < 'A' 
   || input > 'z' 
   || (input > 'Z' && input < 'a')
   ) {  return -1; }
  // '[' is the character after Z, 97 is ascii 'a'
  // Case where selection is lowercase
  if (input >= 'a' && input <= 'z') {
    if (input < menu_option) return (input - 97);
    if (menu_option >= 'A' && menu_option <= '[') return (input - 97);
    else return -1;
  }
  // Case where selection is uppercase
  if (input >= 'A' && input <= 'Z') {
    if (menu_option >= 'a' && input <='z') return -1;
    if (menu_option == 'A') return -1;
    // Magic number is magic, trust
    else return (input - 39);
    // jk actually it's just 26-'A'
  }
  // Failsafe
  return false; 
}

bool UI::BinaryChoice() {
  char input = '*'; // 42
  while (input != 'y' && input != 'n') {
    std::cin >> input;
    if (input == '?') {
      char help = HelpMenu();
    }
  }
  std::cout << std::endl;
  return (input == 'y');
}

int UI::IntChoice(int min, int max) {
  int choice = min - 1;
  while (choice < min || choice > max) {   
    std::string input = "";
    std::getline(std::cin, input);
    if (input[0] == '?') {
      char help = HelpMenu();
    }
    try {
      choice = std::stoi(input);
    } catch (std::exception& e) { choice = min - 1; }
  }
  std::cout << std::endl;
  return choice;
}

std::string UI::StringChoice() {
  char ch;
  while (std::cin.get(ch) && ch != '\n');
  std::string input = "";
  std::getline(std::cin, input);
  std::cout << std::endl;
  return input;
}

int UI::GetNumReinforcements (Player* player, Territory* to_reinforce) {
  int reinforcements = player->get_reinforcements();
  std::cout << "How many armies (1-" << std::to_string(reinforcements) << ") do you want to place in " << to_reinforce->get_name() << "?" << std::endl;
  int armies = IntChoice(1, reinforcements);
  std::cout << armies << " armies have been added to " << to_reinforce->get_name() << "." << std::endl;
  return armies;
}

int UI::GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending) {
  std::cout << "Player " << attacking->get_owner()->get_id() << " prevails!" << std::endl;
  std::cout << "How many armies (" << min << "-" << max << ") would you like to move from "
            << attacking->get_name() << " to " << defending->get_name() << "?" << std::endl;
  return IntChoice(min, max);
}

void UI::StartPhase(Player* player, std::string phase_name) {
    std::cout << "\n-== PLAYER " << player->get_id() << " (" << player->get_name() << "): " << phase_name << " ==-\n" << std::endl;
}



bool UI::AttackChoice() {
  std::cout << "Do you want to attack (y/n)?" << std::endl;
  return BinaryChoice();
}

bool UI::AutoAttackChoice() {
  std::cout << "Do you want to auto-attack (y/n)?" << std::endl;
  return BinaryChoice();
}

bool UI::ContinueAttackChoice() {
  std::cout << "Do you want to continue attacking (y/n)?" << std::endl;
  return BinaryChoice();
}

Territory* UI::GetAttackingTerritory(Player* player) {
  std::vector<Territory*> territories = player->AttackingTerritories();
  if (territories.size() == 0) {
    return NULL;
  }
  std::cout << "Which territory would you like to attack from?" << std::endl;
  return TerritoryMenu(territories);
}

Territory* UI::GetDefendingTerritory(Player* player, Territory* attacking) {
  std::vector<Territory*> territories = player->AttackableTerritories(attacking);
  std::cout << "Which territory would you like to attack from " << attacking->get_name() << "?" << std::endl;
  return TerritoryMenu(territories);
}

char UI::HelpMenu() { 
  std::cout << "You asked for help! But none was available." << std::endl;
  return '*'; 
}

void UI::Attack(Territory* attacking, Territory* defending) {
  std::vector<int> atk_dice = attacking->get_owner()->get_last_roll();
  std::vector<int> def_dice = defending->get_owner()->get_last_roll();
  std::cout << "Player " << attacking->get_owner()->get_id() << " (" << attacking->get_owner()->get_name() << ") rolls ";
  for (auto die : atk_dice) {
    std::cout << die << " ";
  }
  std::cout << "\nPlayer " << defending->get_owner()->get_id() << " (" << defending->get_owner()->get_name() << ") rolls ";
  for (auto die : def_dice) {
    std::cout << die << " ";
  }
  std::cout << std::endl;
}

void UI::DecrementUnits(Territory* victim) {
  std::cout << "Player " << victim->get_owner()->get_id()<< " loses a unit!" << std::endl;
}

void UI::Retreat(Territory* attacking) {
  std::cout << "Player " << attacking->get_owner()->get_id() << "'s army in " << attacking->get_name() 
            << ", humbled by the defenders, retreats!" << std::endl;
}

void UI::CaptureAnnouncement(int conquerors, Territory* attacking, Territory* defending) {
  std::cout << conquerors << " units have been moved from " << attacking->get_name() << " to "
            << defending->get_name() << "! " << attacking->get_num_units() << " units remain in "
            << attacking->get_name() << "." << std::endl; 
}

void UI::PrintLogo() {
  std::cout << " ____  _     _\n|  _ \\(_)___| | ___   _\n| |_) | / __| |/ / | | |\n|  _ <| \\__ \\   <| |_| |\n|_|_\\_\\_|___/_|\\_\\\\__, |\n| __ ) _   _ ___(_)___/   ___  ___ ___\n|  _ \\| | | / __| | '_ \\ / _ \\/ __/ __|\n| |_) | |_| \\__ \\ | | | |  __/\\__ \\__ \\\n|____/ \\__,_|___/_|_| |_|\\___||___/___/\n" << std::endl;
}

void UI::GetMapfile(char* filename) {
  std::cout << "Please enter the file name of the .map file to load:" << std::endl;
  strcpy(filename, StringChoice().c_str());
}

int UI::GetNumPlayers(int min, int max) {
  std::cout << "How many players (" << min << "-" << max  << ") are there?" << std::endl;
  return IntChoice(min, max);
}

bool UI::FortificationChoice() {
  std::cout << "Do you want to fortify a territory (y/n)?" << std::endl;
  return BinaryChoice();
}

Territory* UI::GetFortificationSource(std::vector<Territory*> territories) {
  std::cout << "From which of your territories do you want to fortify?" << std::endl;
  return TerritoryMenu(territories);
}

Territory* UI::GetFortificationDestination(Territory* source, std::vector<Territory*> territories) {
  std::cout << "To which adjacent territory will you send troops from " << source->get_name() << "?" << std::endl;
  return TerritoryMenu(territories);
}

int UI::GetNumEmigrants(int max, Territory* source, Territory* destination) {
  std::cout << "How many units (1-" << max << ") will you send from "
            << source->get_name() << " to " << destination->get_name() << "?" << std::endl;
  return IntChoice(1, max);
}

void UI::FortificationComplete(int emigrants, Territory* source, Territory* destination) {
  std::cout << emigrants << " units were sent as fortifications from " << source->get_name()
            << " to " << destination->get_name() << "!" << std::endl;
}

void UI::StartTurn(int turn, Player* player) {
  std::cout << "\n-== TURN " << turn << ": PLAYER " << player->get_id() << " ==-" << std::endl;
}

void UI::PrintHand(Player *player){
	std::deque<Card*> hand = player->get_hand();
	if (hand.size() > 0) {
		std::cout << "Your hand contains a ";
		for (unsigned int i = 0; i < hand.size(); i++) {
			std::cout << hand[i]->get_card_string();
			if (hand.size() > 1 && i < hand.size() - 2) {
				std::cout << ", a ";
			}
			else if (i == hand.size() - 2) {
				std::cout << " and a ";
			}
		}
		std::cout << "." << std::endl;
	}
}

void UI::PrintMatch(Player *player, std::string match, int bonus_reinforcements){
	std::cout << "Player " << player->get_id() << " matched a set of cards (" << match << ") for " << bonus_reinforcements << " additional reinforcements!" << std::endl;
}

void UI::EndGame(Player* winner) {
  std::cout << "  ____    ____  __    ______ .___________.  ______   .______     ____    ____  __" << std::endl;
  std::cout << "\\   \\  /   / |  |  /      ||           | /  __  \\  |   _  \\    \\   \\  /   / |  |" << std::endl;
  std::cout << " \\   \\/   /  |  | |  ,----'`---|  |----`|  |  |  | |  |_)  |    \\   \\/   /  |  |" << std::endl;
  std::cout << "  \\      /   |  | |  |         |  |     |  |  |  | |      /      \\_    _/   |  |" << std::endl;
  std::cout << "   \\    /    |  | |  `----.    |  |     |  `--'  | |  |\\  \\----.   |  |     |__|"  << std::endl;
  std::cout << "    \\__/     |__|  \\______|    |__|      \\______/  | _| `._____|   |__|     (__) " << std::endl;
  std::cout << "=================================================================================" << std::endl;
  std::cout << winner->get_name() << " (Player " << winner->get_id() << ") is the WINNER!" <<std::endl;
  std::cout << "Gaze upon their works, ye mighty, and tremble!" << std::endl;
  std::cout << "Team Risky Business (1983) thanks you for playing!" <<std::endl;                                                                                 
}

// Shamelessly stolen from NetHack 3.4.3
// Some combination of "imitation is the sincerest form of flattery"
// and "homage is theft"
void UI::KillPlayer(Player* dead_player) {
  std::cout << "                       ----------" << std::endl;
  std::cout << "                      /          \\" << std::endl;
  std::cout << "                     /    REST    \\" << std::endl;
  std::cout << "                    /      IN      \\" << std::endl;
  std::cout << "                   /     PEACE      \\" << std::endl;
  std::cout << "                  /                  \\" << std::endl;
  std::cout << "                  |     PLAYER " << dead_player->get_id() << "     |" << std::endl;
  std::cout << "                  |                  |" << std::endl;
  std::cout << "                  |                  |" << std::endl;
  std::cout << "                  |                  |" << std::endl;
  std::cout << "                  |                  |" << std::endl;
  std::cout << "                  |                  |" << std::endl;
  std::cout << "                  |       2015       |" << std::endl;
  std::cout << "                 *|     *  *  *      | *" << std::endl;
  std::cout << "        _________)/\\\\_//(\\/(/\\)/\\//\\/|_)_______" << std::endl;
}

// These declarations have to be here to keep the compiler happy
std::vector<PlayerView*> UI::player_views;
Stats* UI::stats = 0;