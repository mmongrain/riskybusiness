#include "card.h"
#include "deck.h"
#include "territory.h"
#include <iostream>

// Demo main for deck
int main(){

	// Create instance of the deck
	// Deck is a singleton class, so use Deck::Instance() to call methods
	// (Do not instantiate Deck)
	Deck::Instance();

	// Createa vector of territories 
	// To be passed as parameter to Generate()
	std::vector<Territory*> territories;
	for (int i = 0; i < 10; ++i){
		territories.push_back(new Territory());
	}
	Deck::Instance().Generate(territories);
	std::deque<Card*> my_cards = Deck::Instance().getCards();
	std::cout << "The deck has been generated! \nHere are the contents of your deck:\n" << std::endl;
	for (Card *card : my_cards){
		std::cout << card->get_card_string() << " ";
	}

	// Draw a card, display the drawn card and the remaining deck
	Card *my_card = Deck::Instance().Draw();

	std::cout << "\n\nYou drew a " << my_card->get_card_string() << "!" << std::endl;
	my_cards = Deck::Instance().getCards();
	std::cout << "Your deck now contains:\n" << std::endl;
	for (Card *card : my_cards){
		std::cout << card->get_card_string() << " ";
	}

	// Replace it back into the deck
	Deck::Instance().Replace(my_card);

	std::cout << "\nThank you for replacing your card" << std::endl;
	my_cards = Deck::Instance().getCards();
	std::cout << "Your deck now contains:" << std::endl;
	for (Card *card : my_cards){
		std::cout << card->get_card_string() << " ";
	}

	// Print the cards before shuffling
	my_cards = Deck::Instance().getCards();
	std::cout << "\n\nCards before shuffling:" << std::endl;
	for (Card *card : my_cards){
		std::cout << card->get_card_string() << " ";
	}

	// Shuffle the deck
	Deck::Instance().Shuffle();
	std::cout << "\n\nShuffling..." << std::endl;

	// Print the cards after shuffling
	my_cards = Deck::Instance().getCards();
	std::cout << "\nCards after shuffling:" << std::endl;
	for (Card *card : my_cards){
		std::cout << card->get_card_string() << " ";
	}

	// Clear (empty) the deck
	Deck::Instance().Clear();

	
}