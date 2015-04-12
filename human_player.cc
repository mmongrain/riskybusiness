#include <iostream>

#include "battle.h"
#include "human_player.h"
#include "player.h"
#include "territory.h"
#include "ui.h"

// Asks the user to input the name of a territory and a number of 
// reinforcements, does the necessary checks and performs the reinforcement

void HumanPlayer::Reinforce() {
  CalculateReinforcements();
  while (reinforcements > 0){
    Territory* to_reinforce = UI::GetReinforceableTerritory(this);
    int armies = UI::GetNumReinforcements(this, to_reinforce);
    reinforcements -= armies;
    to_reinforce->set_num_units(to_reinforce->get_num_units() + armies);
  }
}

void HumanPlayer::Attack() {
  bool skip_flag = false;
  UI::StartPhase(this, "ATTACK");
  while (UI::AttackChoice()) {
    Territory *attacking = UI::GetAttackingTerritory(this);
    if (attacking == NULL) { continue; }
    Territory *defending = UI::GetDefendingTerritory(this, attacking);
    if (defending == NULL) { continue; }
    Battle::SingleBattle(attacking, defending);
  }
}

void HumanPlayer::Fortify() {
  if (UI::FortificationChoice()) {
    // AttackingTerritories are also valid source of fortification (all)
    Territory* source = UI::GetFortificationSource(FortifyingTerritories());
    Territory* destination = UI::GetFortificationDestination(source, FortifiableTerritories(source));
    int max = source->get_num_units() - 1;
    int emigrants = UI::GetNumEmigrants(max, source, destination);
    source->set_num_units(source->get_num_units() - emigrants);
    destination->set_num_units(destination->get_num_units() + emigrants);
    UI::FortificationComplete(emigrants, source, destination);
  }
}
