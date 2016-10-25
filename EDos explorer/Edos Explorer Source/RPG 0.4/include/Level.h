#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"

#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class Level
{
    public:
        Level();

        void load(Player &user, char doorChar = ' ');
        void print();
        void moveUser(char input, Player &user);

        char getTile(int x, int y);
        void setTile(int x, int y, char tile);
        void getPoint();
        void nextLevelCheat(Player &user);


    private:
        bool teleportUser(Player &user, int targetX, int targetY);  // tries teleporting user to a tile, false if failed
        int levelNumber=1, roomNumber=0; // Ex. lvl1.0;
        int teleporter1X,teleporter1Y, teleporter2X,teleporter2Y;   // for teleporters
        vector <string> levelMap;
        void processPlayerMove(Player &user, int targetX, int targetY);

        int levelPoints = 0;    // for collecting '$'

        void clearMap();
};

#endif // LEVEL_H
