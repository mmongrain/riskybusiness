#include <stdlib.h> // srand();
#include <time.h>   // time();
#include "game.h"
#include "map.h"
int main(){
  // Creates a random seed for the RNG
  srand(time(NULL));
  
  // Loads the map
  char filename[100] = "World.map";
  Map::Instance().Load(filename);

  // Runs the game
  Game::PlayGame();
	return 0;
}
