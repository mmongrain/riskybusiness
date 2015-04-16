#include "unit-deck.h"
#include "territory.h"
#include <iostream>

int main(){
	std::vector<Territory*> territories;
	for (int i = 0; i < 10; ++i){
		territories.push_back(new Territory());
	}

	UnitDeck::Instance();
	std::cout << "UnitDeck::Instance passed!" << std::endl;
	UnitDeck::Generate(territories);
	std::cout << "UnitDeck::Generate passed!" << std::endl;
	UnitDeck::Draw();
	std::cout << "UnitDeck::Draw passed!" << std::endl;
	UnitDeck::IsEmpty();
	std::cout << "UnitDeck::IsEmpty passed!" << std::endl;
	UnitDeck::Replace(new Card(Card::JOKER));
	std::cout << "UnitDeck::Replace passed!" << std::endl;
	UnitDeck::Shuffle();
	std::cout << "UnitDeck::Shuffle passed!" << std::endl;
	UnitDeck::Clear();
	std::cout << "UnitDeck::Clear passed!" << std::endl;

	std::cout << "All tests passed--unit test successful." << std::endl;
}