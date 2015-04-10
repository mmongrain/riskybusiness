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

void battle::Battle(Territory* attacking, Territory* defending) {
  int result = AttackHandler(attacking, defending);
  if (result == 1) {
    Capture(attacking, defending);
    if (Game::Instance().get_game_over() == true)
      return;
  }
  else {
    Retreat(attacking, result);
  }
}

// for HumanPlayer: will ask if he wants to AutoAttack or to attack only once,
// and then will keep doing SingleAttacks until someone wins or until the Player retreats 
// or until he chooses to AutoAttack (automatically attack until it is no longer possible)
// 
// A CompPlayer will always choose to AutoAttack

int battle::AttackHandler(Territory *attacking, Territory *defending) {
  SingleAttack(attacking, defending);
  if (defending->get_num_units() <= 0)
    return 1; // attacking territory wins     
  else if (attacking->get_num_units() <= 1)
    return 2; // attacking territory loses      
}

int battle::AutoAttack(Territory *attacking, Territory *defending){
  while (attacking->get_num_units() > 1 && defending->get_num_units() > 0){
    SingleAttack(attacking, defending);
  }
  if (defending->get_num_units() <= 0)
    return 1; // attacking territory wins
  else
    return 2; // attacking territory loses
}

void battle::SingleAttack(Territory *attacking, Territory *defending){
  int num_atk_dice = DetermineAtkDice(attacking);
  int num_def_dice = DetermineDefDice(defending);
  std::vector<int> atk_dice = Dice(num_atk_dice);
  attacking->set_num_units(attacking->get_num_units() - atk_dice.size());
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
      attacking->get_owner()->RemoveDie();
      UI::DecrementUnits(attacking); 
    }
  }
}

void battle::Capture(Territory* attacking, Territory* defending){
  std::cout << attacking->get_name() << " (Player " << attacking->get_owner()->get_id() << ") has prevailed!" << std::endl;
  int min = attacking->get_owner()->get_last_roll().size();
  int max = attacking->get_num_units() - 1;
  min = (min > max) ? max : min;
  attacking->get_owner()->CaptureTerritory(attacking, defending, min, max);
}

void battle::Retreat(Territory* attacking, int result){
  if (result == 2)
    std::cout << "The attacking army, humbled, retreats!" << std::endl;
  else
    std::cout << "The attacking army chose to retreat" << std::endl;
}

int battle::DetermineAtkDice(Territory* attacking){
  if (attacking->get_num_units() < 3)
    return attacking->get_num_units() - 1;
  else return 3;
}

int battle::DetermineDefDice(Territory* defending){
  if (defending->get_num_units() < 2)
    return 1;
  else return 2;
}

// move this baby to Territory, it belongs there


// Rolls between one and three dice--no more, no less.
// Returns and displays a vector of up to three ints or -1 if input is invalid
std::vector<int> battle::Dice(int num_dice) {
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
