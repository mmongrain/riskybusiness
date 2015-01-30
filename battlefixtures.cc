#include <iostream>
#include "battlefixtures.hh"

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

	bool Country::are_adjacent (Country* attacking, Country* defending) {
		if (attacking->owner != defending->owner) {
			return true;
		} else return false;
	}

}
