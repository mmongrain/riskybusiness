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

char UI::HelpMenu() { 
  std::cout << "You asked for help! But none was available." << std::endl;
  return '*'; 
}