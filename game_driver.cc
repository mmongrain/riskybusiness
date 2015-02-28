#include <iostream>
#include <stdlib.h> // srand();
#include <time.h>   // time();
#include "game.h"

int main(){
  // Creates a random seed for the RNG
  srand(time(NULL));
	std::cout << "Let the game begin!" << std::endl;
  
  // Loads the map
  char filename[100] = "World.map";
  Map::Instance().Load(filename);

  // Runs the game
  Game::Instance().PlayGame();
	return 0;
}
