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
  for (unsigned int i = 0; i < territories.size(); i++) {
    std::cout << menu_option << ") " << territories[i]->get_name() << std::endl;
    ++menu_option;
  }
  while (input < 'a' || input >= menu_option) {
    std::cin >> input;
    if (input == '?') {
      char help = HelpMenu();
    }
  }
  int which_territory = (int)input - (int)'a';

  return territories[which_territory];
}

int UI::GetNumReinforcements (Player* player, Territory* to_reinforce) {
  int armies = 0;
  int reinforcements = player->get_reinforcements();
  std::cout << "How many armies (1-" << std::to_string(reinforcements) << ") do you want to place in " << to_reinforce->get_name() << "?" << std::endl;
  while (armies < 1 || armies > reinforcements)
  {   
    std::string input = "";
    std::getline(std::cin, input);
    if (input[0] == '?') {
      char help = HelpMenu();
    }
    try {
      armies = std::stoi(input);
    }
    catch (std::exception& e) {}
  }
  std::cout << armies << " armies have been added to " << to_reinforce->get_name() << "." << std::endl;
  return armies;
}

void UI::StartAttackPhase(Player* player) {
    std::cout << "\n-== PLAYER " << player->get_id() << " (" << player->get_name() << "): ATTACK PHASE ==-\n" << std::endl;
}

bool UI::AttackPhase(Player* player) {
  char input = '*';
  std::cout << "Do you want to attack (y/n)?" << std::endl;
  while (input != 'y' && input != 'n') {
    std::cin >> input;
    if (input == '?') {
    char help = HelpMenu();
    }
  }

  return (input == 'y');
}

Territory* UI::GetAttackingTerritory(Player* player) {
  char menu_option = 'a';
  char input = '*';
  std::vector<Territory*> territories = player->AttackingTerritories();
  std::cout << "\nWhich territory would you like to attack from?" << std::endl;
  for (unsigned int i = 0; i < territories.size(); i++) {
    std::cout << menu_option << ") " << territories[i]->get_name() << std::endl;
    ++menu_option;
  }
  while (input < 'a' || input >= menu_option) {
    std::cin >> input;
    if (input == '?') {
      char help = HelpMenu();
    }
  }
  int which_territory = (int)input - (int)'a';

  return territories[which_territory];
}

Territory* UI::GetDefendingTerritory(Player* player, Territory* attacking) {
  char menu_option = 'a';
  char input = '*';
  std::vector<Territory*> territories = player->AttackableTerritories(attacking);
  std::cout << "\nWhich territory would you like to attack from " << attacking->get_name() << "?" << std::endl;
  for (unsigned int i = 0; i < territories.size(); i++) {
    std::cout << menu_option << ") " << territories[i]->get_name() << std::endl;
    ++menu_option;
  }
  while (input < 'a' || input >= menu_option) {
    std::cin >> input;
    if (input == '?') {
      char help = HelpMenu();
    }
  }
  int which_territory = (int)input - (int)'a';

  return territories[which_territory];
}

bool UI::AutoAttack(){
  char answer;
  std::cout << "Do you want to auto-attack (y/n)?" << std::endl;
  std::cin >> answer;
  while (input != 'y' && input != 'n') {
    std::cin >> input;
    if (input == '?') {
    char help = HelpMenu();
    }
    return (answer == 'y');
}

char UI::HelpMenu() { 
  std::cout << "You asked for help! But none was available." << std::endl;
  return '*'; 
}

void UI::Attack(Territory* attacking, Territory* defending) {
  std::vector<int> atk_dice = attacking->get_last_roll();
  std::vector<int> def_dice = defending->get_last_roll();
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