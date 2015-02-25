#include <vector>
#include <string>
#include <iostream>

#include "observer.h"
#include "player_view.h"

PlayerView::PlayerView(Player *player) { 
  this->player = player;
  player.add_observer(this);
}

PlayerView::~PlayerView() {
  player.remove_observer(this);
}

void PlayerView::Update() {
  territories = player.get_owned_territories();
  continents = player.get_owned_continents();
  reinforcements = player.get_reinforcements();
  armies = player.get_armies();
  battles = player.get_battles();
  std::cout << this->to_string();
}

std::string PlayerView::to_string() {
  std::string out = "[" + player.get_name() + "]\nTerritories controlled: ";
  for (int i = 0; i < territories.size(); i++) {
    out += territories[i].get_name();
    (i < territories.size() - 1) ? out += ", " : out += ".\n";
  }
  out += "Continents controlled: ";
  for (int i = 0; i < continents.size(); i++) {
    out += continents[i].get_name();
    (i < continents.size() - 1) ? out += ", " : out += ".\n";
  }
  out += "Armies: " + std::to_string(armies) + "\nBattles won: " +
         std::to_string(battles) + "Current no. of reinforcements: " +
         std::to_string(reinforcements) + "\n";
  return out;
}
