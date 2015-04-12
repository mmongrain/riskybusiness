#include <iostream>

#include "battle.h"
#include "human_player.h"
#include "player.h"
#include "territory.h"
#include "ui.h"

// Asks the user to input the name of a territory and a number of 
// reinforcements, does the necessary checks and performs the reinforcement

void HumanPlayer::Reinforce() {
  UI::StartPhase(this, "REINFORCEMENT");
  CalculateReinforcements();
  while (reinforcements > 0){
    Territory* to_reinforce = UI::GetReinforceableTerritory(this);
    int armies = UI::GetNumReinforcements(this, to_reinforce);
    reinforcements -= armies;
    to_reinforce->set_num_units(to_reinforce->get_num_units() + armies);
  }
}

void HumanPlayer::Attack() {
  UI::StartPhase(this, "ATTACK");
    while (UI::AttackChoice() && AttackingTerritories().size() > 0) {
      if (AttackingTerritories().size() > 0) {
        Territory *attacking = UI::GetAttackingTerritory(this);
        if (attacking == NULL) { continue; }
        Territory *defending = UI::GetDefendingTerritory(this, attacking);
        if (defending == NULL) { continue; }
        Battle::SingleBattle(attacking, defending);
     } else { 
      UI::StatusMessage("You have no territories that you can attack from!"); 
      return;
    }
  }
} 

void HumanPlayer::Fortify() {
  UI::StartPhase(this, "FORTIFICATION");
  if (FortifyingTerritories().size() > 0) {
    while (UI::FortificationChoice()) {
      Territory* source = UI::GetFortificationSource(FortifyingTerritories());
      Territory* destination;
      if (FortifiableTerritories(source).size() > 0) {
        destination = UI::GetFortificationDestination(source, FortifiableTerritories(source));
      } else {
        UI::StatusMessage("No territories can be reinforced from there!");
        continue;
      }
      int max = source->get_num_units() - 1;
      int emigrants = UI::GetNumEmigrants(max, source, destination);
      source->set_num_units(source->get_num_units() - emigrants);
      destination->set_num_units(destination->get_num_units() + emigrants);
      UI::FortificationComplete(emigrants, source, destination);
      break;
    }
  } else { UI::StatusMessage("You have no territories that you can fortify from!"); }
}
