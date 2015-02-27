#include "map.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main () {
  char filein[100] = "World.map";
  char fileout[100] = "TestOut.map";
  Map::Instance().Load(filein);
  Map::Instance().Save(fileout);
  return 0;
}
