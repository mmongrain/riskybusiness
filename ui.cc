#include <exception>
#include <iostream>
#include <vector>
#include <string>
#include "territory.h"
#include "player.h"
#include "ui.h"

Territory* UI::GetReinforceableTerritory (Player* player) {
  char menu_option = 'a';
  char input = '*';
  std::vector<Territory*> territories = player->get_owned_territories();
  int reinforcements = player->get_reinforcements();
  std::cout << "You have " << std::to_string(reinforcements) << " reinforcements."
        << "\nWhich territory would you like to reinforce? " << std::endl;
  return UI::TerritoryMenu(territories);
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
  return territories[choice];
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
    if (menu_option >= 'A' && input <= '[') return (input - 97);
    else return -1;
  }
  // Case where selection is uppercase
  if (input >= 'A' && input <= 'Z') {
    if (menu_option >= 'a' && input <='z') return -1;
    if (menu_option == 'A') return -1;
    // Magic number is magic, trust
    else return (input - 39);
    // JK Actually it's just -'A'+26
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
  return choice;
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

void UI::StartAttackPhase(Player* player) {
    std::cout << "\n-== PLAYER " << player->get_id() << " (" << player->get_name() << "): ATTACK PHASE ==-\n" << std::endl;
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
  char input = '*';
  std::vector<Territory*> territories = player->AttackingTerritories();
  std::cout << "\nWhich territory would you like to attack from?" << std::endl;
  return TerritoryMenu(territories);
}

Territory* UI::GetDefendingTerritory(Player* player, Territory* attacking) {
  char input = '*';
  std::vector<Territory*> territories = player->AttackableTerritories(attacking);
  std::cout << "\nWhich territory would you like to attack from " << attacking->get_name() << "?" << std::endl;
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
