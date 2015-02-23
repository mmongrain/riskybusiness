#include "map.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main () {
  char filein[100] = "World (small).map";
  char fileout[100] = "TestOut.map";
  Map map(filein);
  map.Save(fileout);
  return 0;
}
