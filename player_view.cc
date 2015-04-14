#include <vector>
#include <string>

#include "observer.h"
#include "player.h"
#include "player_view.h"
#include "game.h"
#include "territory.h"
#include "continent.h"
#include "ui.h"

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
  if (Game::Instance().verbose_mode) {
    UI::StatusMessage(to_string());
  }
}

std::string PlayerView::to_string() {
  std::string out = "[" + std::to_string(player->get_id()) + "]: ";
  for (unsigned int i = 0; i < continents.size(); i++) {
    out += continents[i]->get_name();
    (i < continents.size() - 1) ? out += ", " : out += ".";
  }
  return out;
}
