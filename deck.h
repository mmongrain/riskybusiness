#ifndef DECK_H_
#define DECK_H_

#include <vector>

class Card;
class Deck { 
  public:
    // SINGLETON
    static Deck &Instance() {
      static Deck instance;
      return instance;
    }
    Deck() {};
    Deck(Deck const&);
    void operator=(Deck const&);
    // END SINGLETON

    void Clear();
    Card* Draw();
    std::vector<Card*> Draw(int num_cards);
    void Generate();
    void Replace(Card* card);
    void Replace(std::vector<Card*> cards);
    void Shuffle();

  private:
    std::vector<Card*> cards;
};

#endif
