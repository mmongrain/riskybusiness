#ifndef UI_H_
#define UI_H_

class Territory;
class Player;

class UI {
  public:
    static Territory* GetReinforceableTerritory(Player* player);
    static int GetNumReinforcements(Player* player, Territory* to_reinforce);
    static char HelpMenu();
    static void StartAttackPhase(Player* player);
    static bool AttackPhase(Player * player);
    static Territory* GetAttackingTerritory(Player* player);
    static Territory* GetDefendingTerritory(Player* player, Territory* attacking_territory);
    static void Attack(Territory* attacking, Territory* defending);
    static void DecrementUnits(Territory* victim);
};

#endif