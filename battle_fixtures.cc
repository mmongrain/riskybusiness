#include <iostream>
#include "battlefixtures.h"

// This class does more or less nothing other than just store data!
// are_adjacent() is the most crucial function from the point of view of the
// Battle system. Here it is modeled just as "the two countries are not
// the same", which is sufficient for modeling a single battle.

namespace battle {
  Country::Country () {
    owner = -1;
    units = -1;
  }

  Country::Country (int owned, int united) {
    owner = owned;
    units = united;
  }

  Country::~Country () {};

  bool Country::AreAdjacent (Country* attacking, Country* defending) {
    if (attacking->owner != defending->owner) {
      return true;
    } else return false;
  }

}
