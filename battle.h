#ifndef BATTLE_H
#define BATTLE_H

bool attack_is_valid(Country attacking, Country defending, int atk_dice, int def_dice, string out);
int dice(int number, int[] results);
int attack(Country attacking, Country defending, int atk_dice, int def_dice, bool all_in);
int all_in_attack(Country attacking, Country defending);
int victory(Country attacking, Country defending, int atk_dice, int num_units);

