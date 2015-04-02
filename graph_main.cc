#include "map.h"

int main() {
  srand(time(NULL));
  char FILENAME[100] = "WorldBad.map";
  Map::Instance().Load(FILENAME);
  return 0;
}
