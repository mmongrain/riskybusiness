#ifndef UNIT_DECK_H
#define UNIT_DECK_H

#include <string>

#include "deck.h"
#include "card.h"

class UnitDeck {
public:
	static void Instance();	
	static void Generate(std::vector<Territory*> territories);
	static void Draw();	
	static void IsEmpty();
	static void Replace(Card* card);
	static void Shuffle();
	static void Clear();
};

#endif
