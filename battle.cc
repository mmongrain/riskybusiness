#include <iostream>
#include <stdlib.h> // rand()
#include <algorithm> // sort()
#include <functional> // greater()
#include <vector>
#include <time.h> // time()

#include "ui.h"
#include "battle.h"
#include "game.h"
#include "human_player.h" 

void Battle::SingleBattle(Territory* attacking, Territory* defending) {
  int result = AttackHandler(attacking, defending);
  if (result == 1) {
    Capture(attacking, defending);
  } else { UI::Retreat(attacking); }
}

// for HumanPlayer: will ask if he wants to AutoAttack or to attack only once,
// and then will keep doing SingleAttacks until someone wins or until the Player retreats 
// or until he chooses to AutoAttack (automatically attack until it is no longer possible)
// 
// A CompPlayer will always choose to AutoAttack

int Battle::AttackHandler(Territory *attacking, Territory *defending) {
  // If user wants to autoattack, keep attackin' till someone wins
  if (UI::AutoAttackChoice()) {
    while (attacking->get_num_units() > 1 && defending->get_num_units() > 0) { 
      SingleAttack(attacking, defending);
        if (defending->get_num_units() <= 0) return 1; // attacking territory wins     
        if (attacking->get_num_units() <= 1) return 2; // attacking territory loses
    }
  }
  SingleAttack(attacking, defending);
  if (defending->get_num_units() <= 0) return 1; // attacking territory wins     
  if (attacking->get_num_units() <= 1) return 2; // attacking territory loses
  while (UI::ContinueAttackChoice()) {
    SingleAttack(attacking, defending);
    if (defending->get_num_units() <= 0) return 1; // attacking territory wins     
    else if (attacking->get_num_units() <= 1) return 2; // attacking territory loses
  }
}

void Battle::SingleAttack(Territory *attacking, Territory *defending){
  int num_atk_dice = DetermineAtkDice(attacking);
  int num_def_dice = DetermineDefDice(defending);
  std::vector<int> atk_dice = Dice(num_atk_dice);
  attacking->get_owner()->set_last_roll(atk_dice);
  std::vector<int> def_dice = Dice(num_def_dice);
  defending->get_owner()->set_last_roll(def_dice);
  UI::Attack(attacking, defending);
  for (unsigned int i = 0; i < def_dice.size() && i < atk_dice.size(); i++) {
    if (atk_dice[i] > def_dice[i] && defending->get_num_units() != 0) {
      defending->set_num_units(defending->get_num_units() - 1);
      UI::DecrementUnits(defending);
    } else { 
      attacking->set_num_units(attacking->get_num_units() - 1);
      UI::DecrementUnits(attacking); 
    }
  }
}

void Battle::Capture(Territory* attacking, Territory* defending){
  Player* winner = attacking->get_owner();
  Player* loser = defending->get_owner();
  int min = winner->get_last_roll().size();
  int max = attacking->get_num_units() - 1;
  min = (min > max) ? max : min;
  int answer = UI::GetNumConqueringArmies(min, max, attacking, defending);
  defending->set_num_units(answer);
  attacking->set_num_units(attacking->get_num_units() - answer);
  defending->get_owner()->remove_territory(defending);
  if (loser->get_owned_territories().size() == 0) {
    loser->TransferHand(winner);
    Game::Instance().KillPlayer(loser);
  }
  defending->set_owner(winner);
  winner->add_territory(defending); 
  if (winner->owned_territories.size() == Map::Instance().get_territories()->size()){
    Game::Instance().set_game_over(true);
  }
  winner->set_card_this_turn(true);
  UI::CaptureAnnouncement(answer, attacking, defending);
}

int Battle::DetermineAtkDice(Territory* attacking){
  if (attacking->get_num_units() < 3)
    return attacking->get_num_units() - 1;
  else return 3;
}

int Battle::DetermineDefDice(Territory* defending){
  if (defending->get_num_units() < 2)
    return 1;
  else return 2;
}

// Rolls between one and three dice--no more, no less.
// Returns and displays a vector of up to three ints or -1 if input is invalid
std::vector<int> Battle::Dice(int num_dice) {
  std::vector<int> out;
  if (num_dice < 1 || num_dice > 3) {
    out.push_back(-1);
    return out;
  }
  else {
    for (int i = 0; i < num_dice; i++)
    {
      // Generates a random int between 1 and 6.
      out.push_back(std::rand() % 6 + 1);
    }
    // Sorts the vector, from begin() to end(), using the > operator
    std::sort(out.begin(), out.end(), std::greater<int>());
    return out;
  }
}
