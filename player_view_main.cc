#include "player.h"
#include "player_view.h"
#include "human_player.h"

int main () {
  Player *player = new HumanPlayer();
  PlayerView *player_view = new PlayerView(player);

  player->NotifyObservers();

  delete player;
  delete player_view;
}
