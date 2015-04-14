#ifndef _MAP_EDITOR_H
#define _MAP_EDITOR_H

class MapEditor {
    
  public:
    
    static void StartMapEditor();
    static void NewMap();
    static void ExistingMap();
    static void NewMapContinents();
    static void NewMapTerritories();
    static void AddContinent();
    static void AddTerritory();
    static void RemoveContinent();
    static void RemoveTerritory();
    static void NewMapAdjacencies();
    static void NewAdjacency();
    static bool SaveMap();
    static void EditMenu();
    static bool VerifyMapCorrectness();
    
};

#endif
