#include "continent.h"
#include <string>

std::string Continent::ToString() {
  std::string out = "";
  out = get_name() + "=" + std::to_string(get_bonus());
  return out;
}

