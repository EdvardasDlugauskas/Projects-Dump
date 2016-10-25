#ifndef MAP2D_H
#define MAP2D_H

//#include "Army.h"
#include "Colors.h"
#include "Random.h"
#include "Unit.h"

#include <string>
#include <windows.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

class Army;
using namespace std;

        struct tile
        {
            int X, Y;
            char upLayer, botLayer;
            Unit* unitStationed = nullptr;

            // else...?
        };


class Map2D
{
    public:
        void loadMap(string levelMapName);
        void printMap();

        void setUpTile(int x, int y, char tileChar);
        char getTile(int x, int y);

        COORD armyCoord[4]; // constants : first (0) is for user, seconds (1) is for enemy

        tile* getLayerTile(COORD tileCoord) { return &layers[tileCoord.Y][tileCoord.X];}

        void placeArmies(vector<Army *> armies);
        void placeBarbaricArmies(Army* army);
        void placeLegion(Army* army);
        void placeUnit (Unit* placedUnit, COORD placeTile);
        bool moveUnit (Unit* placedUnit, int direction);
        bool moveUnitTo (Unit* placedUnit, COORD placingCoord);
        void updateTile(COORD* tileCoord);

        int getMapWidth(){ return mapWidth; }


    private:
        string mapName;

        vector< vector<tile> > layers;

        int mapWidth = 0, mapHeight = 0;

};

#endif // MAP2D_H
