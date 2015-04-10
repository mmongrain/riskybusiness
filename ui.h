#ifndef UI_H_
#define UI_H_

class Territory;
class Player;

class UI {
  public:
    static Territory* GetReinforceableTerritory(Player* player);
    static int GetNumReinforcements(Player* player, Territory* to_reinforce);
    static char HelpMenu();
    static void StartAttackPhase();
    static bool AttackPhase(Player * player);
    static Territory* GetAttackingTerritory(Player* player);
    static Territory* GetDefendingTerritory(Territory* attacking_territory);
};

#endif