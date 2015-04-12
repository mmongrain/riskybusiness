#ifndef UI_H_
#define UI_H_

#include <string>
#include <vector>

class Territory;
class Player;
class PlayerView;
class Stats;

class UI {
  public:
    // UI Utility
    static void StatusMessage(std::string message);
    static char HelpMenu();
    static int MenuChoice(char menu_option, char input);
    static Territory* TerritoryMenu(std::vector<Territory*> territories);
    static int StringMenu(std::string title, std::vector<std::string> options);
    static bool BinaryChoice();
    static int IntChoice(int min, int max);
    static std::string StringChoice();

    // Attack Phase UI
    static Territory* GetReinforceableTerritory(Player* player);
    static int GetNumReinforcements(Player* player, Territory* to_reinforce);
    static int GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending);
    static void StartAttackPhase(Player* player);
    static bool AttackChoice();
    static bool AutoAttackChoice();
    static bool ContinueAttackChoice();
    static Territory* GetAttackingTerritory(Player* player);
    static Territory* GetDefendingTerritory(Player* player, Territory* attacking_territory);
    static void Attack(Territory* attacking, Territory* defending);
    static void DecrementUnits(Territory* victim);
    static void Retreat(Territory* attacking);
    static void CaptureAnnouncement(int conquerors, Territory* attacking, Territory* defending);

    // Fortification Phase UI
    static bool FortificationChoice();
    static Territory* GetFortificationSource(std::vector<Territory*> territories);
    static Territory* GetFortificationDestination(Territory* source, std::vector<Territory*> territories);
    static int GetNumEmigrants(int max, Territory* source, Territory* destination);
    static void FortificationComplete(int emigrants, Territory* source, Territory* destination);

    // Game controller UI
    static void PrintLogo();
    static void GetMapfile(char* filename); 
    static int GetNumPlayers(int min, int max);

    // Static data members
    static std::vector<PlayerView*> player_views;
    static Stats* stats;

};

#endif