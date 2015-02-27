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
  units = player->get_total_units();
  victories = player->get_victories();
  std::cout << this->to_string();
}

std::string PlayerView::to_string() {
  std::string out = "[" + player->get_name() + "]\nTerritories controlled: ";
  for (int i = 0; i < territories.size(); i++) {
    out += territories[i]->get_name();
    (i < territories.size() - 1) ? out += ", " : out += ".";
  }
  out += "\nContinents controlled: ";
  for (int i = 0; i < continents.size(); i++) {
    out += continents[i]->get_name();
    (i < continents.size() - 1) ? out += ", " : out += ".";
  }
  out += "\nArmies: " + std::to_string(units) + "\nBattles won: " +
         std::to_string(victories) + "\nCurrent no. of reinforcements: " +
         std::to_string(reinforcements) + "\n";
  return out;
}
