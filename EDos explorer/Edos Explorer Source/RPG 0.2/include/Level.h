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

        void load(Player &user);
        void print();
        void moveUser(char input, Player &user);
        char getTile(int x, int y);
        void setTile(int x, int y, char tile);


    private:
        int levelNumber=1, roomNumber=0; // Ex. lvl1.0;

        struct levelPosition{
            string levelName;
            int xCoordinate, yCoordinate;
        };

        vector <levelPosition> levelSaves;
        vector <string> levelMap;
        void processPlayerMove(Player &user, int targetX, int targetY);
        void clearMap();
};

#endif // LEVEL_H
