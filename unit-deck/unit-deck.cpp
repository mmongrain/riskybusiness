#include "unit-deck.h"
#include "territory.h"
#include "card.h"
#include <cassert>

void UnitDeck::Instance() {
	Deck* deck1 = &Deck::Instance();
	Deck* deck2 = &Deck::Instance();
	assert(deck1 == deck2);
}

void UnitDeck::Generate(std::vector<Territory*> territories){
	Deck::Instance().Generate(territories);
	assert(Deck::Instance().size() == (territories.size() + 2));
}

void UnitDeck::Draw(){
	Card *to_be_drawn = Deck::Instance().getCards().back();
	int size = Deck::Instance().size() - 1;
	Card *my_card = Deck::Instance().Draw();
	assert(to_be_drawn == my_card);
	assert(size == Deck::Instance().size());
}

void UnitDeck::IsEmpty(){
	bool empty = false;
	int size = Deck::Instance().size();
	if (size = 0)
		empty = true;
	assert(Deck::Instance().IsEmpty() == empty);
}

void UnitDeck::Replace(Card* card){
	Card *my_card = new Card(Card::JOKER); 
	int initial_size = Deck::Instance().size();
	Deck::Instance().Replace(my_card);
	Card *replaced_card = Deck::Instance().getCards().front();
	int final_size = Deck::Instance().size();
	assert(my_card == replaced_card);
	assert((initial_size + 1) == final_size);
}

void UnitDeck::Shuffle(){
	bool change = false; // whether the cards in the deck changed order or not
	std::deque<Card*> initial_cards = Deck::Instance().getCards();
	Deck::Instance().Shuffle();
	std::deque<Card*> final_cards = Deck::Instance().getCards();
	for (unsigned int i = 0; i < final_cards.size(); ++i){
		if (initial_cards[i] != final_cards[i]){
			change = true;
			break;
		}
	}
	assert(change);
}

void UnitDeck::Clear(){
	Deck::Instance().Clear();
	assert(Deck::Instance().IsEmpty());
}