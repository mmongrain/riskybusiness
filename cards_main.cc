#include "map.h"
#include "deck.h"
#include "game.h"
#include "player.h"

int main() {
  srand(time(NULL));
  char FILENAME[100] = "World.map";
  Map::Instance().Load(FILENAME);
  Game::Instance().TestHelper(4);
  Deck::Instance().Generate();
  Deck::Instance().Shuffle();
  Deck::Instance().PrintCards();
  std::vector<Player*> players = *(Game::Instance().get_players());
  for (auto player : players) {
    player->PrintHand();
  }
  return 0;
}
