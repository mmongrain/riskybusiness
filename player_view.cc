#include <vector>
#include <string>
#include <iostream>

#include "observer.h"
#include "player_view.h"

PlayerView::PlayerView(Player *player) { 
  this->player = player;
  player->AddObserver(this);
}

PlayerView::~PlayerView() {
  player->RemoveObserver(this);
}

void PlayerView::Update() {
  territories = player->get_owned_territories();
  continents = player->get_owned_continents();
  reinforcements = player->get_reinforcements();
  total_units = player->get_total_units();
  battles_won = player->get_battles_won();
  battles_lost = player->get_battles_lost();
  view_str = to_string();
  //std::cout << to_string();
}

std::string PlayerView::to_string() {
  std::string out = "[" + player->get_name() + "]\nTerritories controlled: ";
  for (unsigned int i = 0; i < territories.size(); i++) {
    out += territories[i]->get_name();
    (i < territories.size() - 1) ? out += ", " : out += ".";
    if (i%3==0){ out += "\n";}
  }
  out += "\nContinents controlled: ";
  for (unsigned int i = 0; i < continents.size(); i++) {
    out += continents[i]->get_name();
    (i < continents.size() - 1) ? out += ", " : out += ".";
    out += "\n";
  }
  out += //"\nArmies: " + std::to_string(units) + "\nBattles won: " +
         //std::to_string(victories) + 
         "\nCurrent no. of reinforcements: " +
         std::to_string(reinforcements) + "\n";
  return out;
}
