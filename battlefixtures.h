#ifndef BATTLEFIXTURES_H
#define BATTLEFIXTURES_H

namespace battle {
	class Country {
		public:
			int owner;
			int units;
			Country () {}
			Country(int owned, int united);
			~Country();
			static bool are_adjacent(Country attacking, Country defending);
	};
}

#endif
