#ifndef UI_H_
#define UI_H_

class Territory;
class Player;

class UI {
  public:
    static Territory* GetReinforceableTerritory(Player* player);
    static int GetNumReinforcements(Player* player, Territory* to_reinforce);
    static int GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending);
    static char HelpMenu();
    static void StartAttackPhase(Player* player);
    static bool AttackChoice();
    static bool AutoAttackChoice();
    static bool ContinueAttackChoice();
    static Territory* GetAttackingTerritory(Player* player);
    static Territory* GetDefendingTerritory(Player* player, Territory* attacking_territory);
    static void Attack(Territory* attacking, Territory* defending);
    static void DecrementUnits(Territory* victim);
    static int MenuChoice(char menu_option, char input);
    static Territory* TerritoryMenu(std::vector<Territory*> territories);
    static bool BinaryChoice();
    static int IntChoice(int min, int max);
    static void Retreat(Territory* attacking);
    static void CaptureAnnouncement(int conquerors, Territory* attacking, Territory* defending);
};

#endif