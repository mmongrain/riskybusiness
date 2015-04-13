#include "human_player.h"
#include "player.h"
#include "territory.h"
#include "ui.h"
#include "battle.h"
#include "strategy.h"

// Asks the user to input the name of a territory and a number of 
// reinforcements, does the necessary checks and performs the reinforcement

void HumanPlayer::Reinforce(Player *player, int reinforcements){
	while (reinforcements > 0){
		Territory* to_reinforce = UI::GetReinforceableTerritory(player);
		int armies = UI::GetNumReinforcements(player, to_reinforce);
		reinforcements -= armies;
		to_reinforce->set_num_units(to_reinforce->get_num_units() + armies);
	}
}

void HumanPlayer::Attack(Player *player){
	while (UI::AttackChoice() && player->AttackingTerritories().size() > 0) {
		if (player->AttackingTerritories().size() > 0) {
			Territory *attacking = UI::GetAttackingTerritory(player);
			if (attacking == NULL) { continue; }
			Territory *defending = UI::GetDefendingTerritory(player, attacking);
			if (defending == NULL) { continue; }
			Battle::SingleBattle(attacking, defending);
		}
		else {
			UI::StatusMessage("You have no territories that you can attack from!");
			return;
		}
	}
}
void HumanPlayer::Fortify(Player *player){
	while (UI::FortificationChoice()) {
		Territory* source = UI::GetFortificationSource(player->FortifyingTerritories());
		Territory* destination;
		if (player->FortifiableTerritories(source).size() > 0) {
			destination = UI::GetFortificationDestination(source, player->FortifiableTerritories(source));
		}
		else {
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
}

int HumanPlayer::GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending) {
	return UI::GetNumConqueringArmies(min, max, attacking, defending);
}

bool HumanPlayer::AutoAttackChoice() {
	return UI::AutoAttackChoice();
}