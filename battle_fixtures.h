#ifndef BATTLE_FIXTURES_H_
#define BATTLE_FIXTURES_H_

namespace battle {
  class Country {
    public:
      int owner;
      int units;
      Country ();
      Country(int owned, int united);
      ~Country();
      static bool are_adjacent(Country* attacking, Country* defending);
  };
}

#endif
