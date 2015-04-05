#include "card.h"
#include "deck.h"
#include "map.h"
#include <stdlib.h> // rand;
#include <algorithm> // random_shuffle;

class Territory;

void Deck::Clear() {
  cards.clear();
  NotifyObservers();
}

Card* Deck::Draw() {
  if (!cards.empty()) {
    Card* card = cards.back();
    cards.pop_back();
    return card;
  }
  else return NULL;
}

void Deck::Generate() {
  std::vector<Territory*> territories = *(Map::Instance().get_territories());
  std::vector<Card*> cards;
  cards.push_back(new Card(Card::JOKER));
  cards.push_back(new Card(Card::JOKER));
  for (int i = 0; i < territories.size(); i++) {
    Card::Type type_;
    switch (i % 3) { 
      case 0: type_ = Card::SOLDIER;
              break;
      case 1: type_ = Card::CAVALRY;
              break;
      case 2: type_ = Card::CANNON;
              break;
    }
    cards.push_back(new Card(type_));
  }
  Clear();
  Replace(cards);
  NotifyObservers();
}

bool Deck::IsEmpty() {
  return (cards.size() == 0);
}

void Deck::PrintCards() {
  for (auto card : cards) {
    std::cout << card->get_card_string() << " ";
  }
  std::cout << std::endl;
}

void Deck::Replace(Card* new_card) {
  cards.push_back(new_card);
  NotifyObservers();
}

void Deck::Replace(std::vector<Card*> new_cards) {
  for (Card* card : new_cards) { 
    cards.push_front(card);
  }
  NotifyObservers();
}

void Deck::Shuffle() {
  std::random_shuffle(cards.begin(), cards.end());
  NotifyObservers();
}
 
