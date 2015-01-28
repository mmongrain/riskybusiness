#include <iostream>
#include "battlefixtures.h"

namespace battle {
	class Country {
	public:
		int owner;
		int units;

		Country () {
			owner = -1;
			units = -1;
		}

		Country (int owned, int united) {
			owner = owned;
			units = united;
		}

		~Country ();
		static bool are_adjacent (Country attacking, Country defending) {
			if (attacking.owner != defending.owner) {
				return true;
			} else return false;
		}

	};
}
