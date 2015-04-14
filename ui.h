#ifndef UI_H_
#define UI_H_

#include <string>
#include <vector>

class Territory;
class Continent;
class Player;
class PlayerView;
class Stats;

class UI {
public:
	// UI Utility
	static void StatusMessage(std::string message);
	static char HelpMenu();
	static void About();
	static void MainHelp();
	static int MenuChoice(char menu_option, char input);
	static Territory* TerritoryMenu(std::vector<Territory*> territories);
	static int StringMenu(std::string title, std::vector<std::string> options);
	static int StringMenu(std::vector<std::string> options);
	static bool BinaryChoice();
	static int IntChoice(int min, int max);
	static std::string StringChoice();
	static void ClearBuffer();

	// Game Loop UI
	static void StartTurn(int turn, Player* player);
	static void EndGame(Player* winner);
	static void KillPlayer(Player* dead_player);

	// Map Editor UI
	static void CreateMapFile(char * filename);
	static void DisplayTerritoriesList(std::vector<Territory*> territories);
	static Continent* ContinentMenu(std::vector<Continent*> continents);

	// Attack Phase UI
	static void PrintHand(Player *player);
	static void PrintMatch(Player *player, std::string match, int bonus_reinforcements);
	static Territory* GetReinforceableTerritory(Player* player);
	static int GetNumReinforcements(Player* player, Territory* to_reinforce);
	static void PrintNumReinforcements(int reinforcers, Territory* to_reinforce);
	static int GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending);
	static void StartPhase(Player* player, std::string phase_name);
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
	static int GetNumAIPlayers(int min, int max);
	static int GetDifficulty();
	static int SingleOrMulti();

	// Static data members
	static std::vector<PlayerView*> player_views;
	static Stats* stats;
};

#endif
