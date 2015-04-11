#include <stdlib.h> // srand();
#include <time.h>   // time();
#include "game.h"

int main(){
  // Creates a random seed for the RNG
  srand(time(NULL));
  // Runs the game
  Game::PlayGame();
  return 0;
}
