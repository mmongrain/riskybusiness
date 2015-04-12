#include <algorithm>
#include <vector>
#include <map>
#include <math.h>

#include "card.h"
#include "continent.h"
#include "deck.h"
#include "game.h"
#include "map.h"
#include "player.h"
#include "territory.h"
#include "ui.h"

Player::Player() :  id(player_id++),
                    reinforcements(0),
                    total_units(0),
                    battles_won(0),
                    battles_lost(0),
                    bonus_reinforcements(0),
                    card_this_turn(false),
                    times_redeemed(0) {
  switch (id) {
    case 1: color = sf::Color::Red;
            break;
    case 2: color = sf::Color::Blue;
            break;
    case 3: color = sf::Color::Magenta;
            break;
    case 4: color = sf::Color::Green;
            break;
    case 5: color = sf::Color::Yellow;
            break;
    case 6: color = sf::Color::Cyan;
            break;
    default: color = sf::Color::Black;
  }
  name = "Player " + std::to_string(id);
  hand = *(new std::deque<Card*>);
}

Player::~Player() {
  // hand is guaranteed to be empty of cards, since TransferHand is called when players
  // are eliminated
  delete &hand;
}

// Plays through a single turn for a player. Used in the round-robin main game loop.
void Player::PlayTurn() {
  CardsHandler();
  Reinforce();
  Attack();
  if (Game::Instance().get_game_over() == true) {
    return;
  }
  Fortify();
  if (get_card_this_turn()) {
    Draw();
  }
}

// Deals with cards at the beginning of each turn.
// Same behaviour for all player descendent classes.
void Player::CardsHandler() {
  // Check to see if the player can march cards and match 'em
  UI::PrintHand(this);
  std::string match = HasMatch();
  if (match.length() > 0) {
    Match();
    UI::PrintMatch(this, match);
  }
}

// Draws a single card from the Deck and sends a status message to the UI.
void Player::Draw() {
  if (hand.size() == 5) {
    UI::StatusMessage("You could have drawn a card, but your hand is already full!");
  } else if (Deck::Instance().IsEmpty()) {
    UI::StatusMessage("You would have drawn a card, but the deck is empty!");
  } else {
    hand.push_back(Deck::Instance().Draw());
    UI::StatusMessage("You drew a " + hand.back()->get_card_string() + "!");
  }
  set_card_this_turn(false);
  return;
}

int Player::player_id = 1;

void Player::DetermineContinentOwnership() {
  std::map<Continent*, unsigned int> ownership;
  for (unsigned int i = 0; i < owned_territories.size(); i++) {
    Continent *temp = owned_territories[i]->get_continent();
    if (ownership[temp]) {
      ownership[temp] = ownership[temp] + 1;
    }
    else {
      ownership[temp] = 1;
    }
  }
  for (auto &it : ownership) {
    if (it.first->get_territories().size() == it.second) {
      if (std::find(owned_continents.begin(), owned_continents.end(), it.first) == owned_continents.end()) {
        owned_continents.push_back(it.first);
      }
    }
    else {
      owned_continents.erase(std::remove(owned_continents.begin(), owned_continents.end(), it.first), owned_continents.end());
    }
  }
}

void Player::CalculateReinforcements() {
  DetermineContinentOwnership();
  reinforcements = owned_territories.size() / 3;
  if (reinforcements < 3) {
        reinforcements = 3;
  }
  for (unsigned int i = 0; i < owned_continents.size(); i++) {
    reinforcements += owned_continents[i]->get_bonus();
  }
  reinforcements += bonus_reinforcements;
  bonus_reinforcements = 0;
}

void Player::TransferHand(Player* winner) {
  while (!this->hand.empty()) {
    if (winner->hand.size() < 5) {
      winner->hand.push_back(this->hand.back());
      hand.pop_back();
    } else {
      Deck::Instance().Replace(this->hand.back());
      this->hand.pop_back();
    }
  }
}

void Player::add_continent(Continent *new_continent) {
  for (auto &continent : owned_continents) {
    if (continent == new_continent) { 
      return; 
    }
  }
  owned_continents.push_back(new_continent);
  NotifyObservers();
}

void Player::add_territory(Territory *new_territory) {
  for (auto &territory : owned_territories) {
    if (territory == new_territory) { 
      return; 
    }
  }
  owned_territories.push_back(new_territory);
  NotifyObservers();
}

void Player::remove_territory(Territory *old_territory) {
  owned_territories.erase(std::remove(owned_territories.begin(), owned_territories.end(), old_territory), owned_territories.end());
  NotifyObservers();
}

void Player::remove_continent(Continent *old_continent) {
  owned_continents.erase(std::remove(owned_continents.begin(), owned_continents.end(), old_continent), owned_continents.end());
  NotifyObservers();
}

void Player::add_card(Card *new_card) {
  for (auto &card : hand) {
    if (card == new_card) { 
      return; 
    }
  }
  hand.push_back(new_card);
  NotifyObservers();
}

void Player::remove_card(Card *old_card) {
  hand.erase(std::remove(hand.begin(), hand.end(), old_card), hand.end());
  NotifyObservers();
}

void Player::set_reinforcements(int reinforcements) {
  this->reinforcements = reinforcements;
  NotifyObservers();
}

void Player::set_total_units(int units) {
  this->total_units = units;
  NotifyObservers();
}

void Player::set_name(std::string name) {
  this->name = name;
  NotifyObservers();
}

void Player::set_battles_won(int battles_won) {
  this->battles_won = battles_won;
  NotifyObservers();
}

void Player::set_battles_lost(int battles_lost) {
  this->battles_lost = battles_lost;
  NotifyObservers();
}

void Player::set_card_this_turn(bool card_this_turn) {
  this->card_this_turn = card_this_turn;
  NotifyObservers();
}

void Player::set_last_roll(std::vector<int> last_roll) {
  this->last_roll = last_roll;
  NotifyObservers();
}

// Returns a string describing the match, if one exists.
// Returns null if no match so can be used wherever a bool is used.
std::string Player::HasMatch() {
  int jokers = 0;
  int soldiers = 0;
  int cavalry = 0;
  int cannons = 0;
  for (auto card : hand) {
    switch (card->get_type()) {
      case Card::JOKER: 
        jokers++;
        break;
      case Card::SOLDIER: 
        soldiers++;
        break;
      case Card::CAVALRY: 
        cavalry++;
        break;
      case Card::CANNON: 
        cannons++;
        break;
      default: 
        return "Error in Player::HasMatch()";
    }
  }
  if (soldiers >= 3) {
    return "three soldiers";
  }
  else if (cavalry >= 3) {
    return std::to_string(cavalry) + "three cavalry";
  }
  else if (cannons >= 3) {
    return "three cannons";
  }
  else if (soldiers > 0 && cavalry > 0 && cannons > 0) {
    return "a soldier, a cavalry, and a cannon";
  }
  else if (jokers) {
    if (soldiers == 2) {
      return "two soldiers and a joker";
    }
    else if (cavalry == 2) {
      return "two cavalry and a joker";
    }
    else if (cannons == 2) {
      return "two cannons and a joker";
    }
  }
  return "";
}

void Player::Match() {
  int jokers = 0;
  int soldiers = 0;
  int cavalry = 0;
  int cannons = 0;
  for (auto card : hand) {
    switch (card->get_type()) {
    case Card::JOKER: jokers++;
      break;
    case Card::SOLDIER: soldiers++;
      break;
    case Card::CAVALRY: cavalry++;
      break;
    case Card::CANNON: cannons++;
      break;
    }
  }
  // Taken from Risk 1959 ruleset.
  // This set of conditional logic determines which set to use.
  if (soldiers >= 3) {
    int tracker = 0;
    for (auto card : hand) {
      // Remove 3 (and only 3) soldiers.
      if (tracker > 3) continue;
      if (card->get_type() == Card::SOLDIER) {
        Deck::Instance().Replace(card);
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        tracker++;
      }
    }
  }
  else if (cavalry >= 3) {
    int tracker = 0;
    for (auto card : hand) {
      // Remove 3 (and only 3) cavalry.
      if (tracker > 3) continue;
      if (card->get_type() == Card::CAVALRY) {
        Deck::Instance().Replace(card);
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        tracker++;
      }
    }
  }
  else if (cannons >= 3) {
    int tracker = 0;
    for (auto card : hand) {
      // Remove 3 (and only 3) cannons.
      if (tracker > 3) continue;
      if (card->get_type() == Card::CANNON) {
        Deck::Instance().Replace(card);
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        tracker++;
      }
    }
    // Remove one of each.
  }
  else if (soldiers && cavalry && cannons) {
    bool soldier_found, cavalry_found, cannon_found;
    for (auto card : hand) {
      if (card->get_type() == Card::SOLDIER && !soldier_found) {
        Deck::Instance().Replace(card);
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        soldier_found = true;
      }
      else if (card->get_type() == Card::CAVALRY && !cavalry_found) {
        Deck::Instance().Replace(card);
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        cavalry_found = true;
      }
      else if (card->get_type() == Card::CANNON && !cannon_found) {
        Deck::Instance().Replace(card);
        hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
        cannon_found = true;
      }
    }
  }
  else if (jokers) {
    // Remove two soldiers & a joker
    if (soldiers == 2) {
      bool joker_found;
      int tracker = 0;
      for (auto card : hand) {
        if (card->get_type() == Card::JOKER && !joker_found) {
          Deck::Instance().Replace(card);
          hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
          joker_found = true;
        }
        else if (card->get_type() == Card::SOLDIER && tracker < 2) {
          Deck::Instance().Replace(card);
          tracker++;
        }
      }
      // Remove two cavalry & a joker
    }
    else if (cavalry == 2) {
      bool joker_found;
      int tracker = 0;
      for (auto card : hand) {
        if (card->get_type() == Card::JOKER && !joker_found) {
          Deck::Instance().Replace(card);
          hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
          joker_found = true;
        }
        else if (card->get_type() == Card::CAVALRY && tracker < 2) {
          Deck::Instance().Replace(card);
          hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
          tracker++;
        }
      }
      // Remove two cannons & a joker
    }
    else if (cannons == 2) {
      bool joker_found;
      int tracker = 0;
      for (auto card : hand) {
        if (card->get_type() == Card::JOKER && !joker_found) {
          Deck::Instance().Replace(card);
          hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
          joker_found = true;
        }
        else if (card->get_type() == Card::CANNON && tracker < 2) {
          Deck::Instance().Replace(card);
          hand.erase(std::remove(hand.begin(), hand.end(), card), hand.end());
          tracker++;
        }
      }
    }
  }
  else return;
  bonus_reinforcements = 4;
  for (int i = 0; i < times_redeemed; i++) {
    if (i <= 4) { bonus_reinforcements += 2; }
    else if (i == 5) { bonus_reinforcements += 3; }
    else             { bonus_reinforcements += 5; }
  }
  times_redeemed++;
}

std::vector<Territory*> Player::FortifyingTerritories() {
  std::vector<Territory*> fortifying_territories;
  for (auto territory : owned_territories) {
    if (territory->get_num_units() > 1) {
      if (FortifiableTerritories(territory).size() > 0) {
        fortifying_territories.push_back(territory);
      }
    }
  }
  return fortifying_territories;
}

std::vector<Territory*> Player::FortifiableTerritories(Territory* source) {
  std::vector<Territory*> fortifiable_territories;
  std::vector<Territory*> adjacents = *(source->get_adjacency_list());
  for (auto territory : adjacents) {
    if (territory->get_owner() == this) {
      fortifiable_territories.push_back(territory);
    }
  }
  return fortifiable_territories;
}

std::vector<Territory*> Player::AttackingTerritories() {
  std::vector<Territory*> attacking_territories;
  for (auto territory : owned_territories) {
    if (territory->get_num_units() > 1) {
      std::vector<Territory*> adjacents = *(territory->get_adjacency_list());
      for (auto adjacent : adjacents) {
        if (adjacent->get_owner() != this) {
          std::vector<Territory*>::iterator it;
          it = find(attacking_territories.begin(), attacking_territories.end(), territory);
          if (it == attacking_territories.end()) { attacking_territories.push_back(territory); }
        }
      }
    }
  }
  return attacking_territories;
}

std::vector<Territory*> Player::AttackableTerritories(Territory* attacking) {
  std::vector<Territory*> attackables;
  std::vector<Territory*> adjacents = *(attacking->get_adjacency_list());
  for (auto adjacent : adjacents) {
    if (adjacent->get_owner() != this) {
      attackables.push_back(adjacent);
    }
  }
  return attackables;
}