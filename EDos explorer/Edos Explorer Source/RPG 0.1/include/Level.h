#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"

#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>


using namespace std;


class Level
{
    public:
        Level();

        void load(string fileName, Player &user);
        void print();
        void moveUser(char input, Player &user);
        char getTile(int x, int y);
        void setTile(int x, int y, char tile);

    private:
        vector <string> levelMap;
        void processPlayerMove(Player &user, int targetX, int targetY);
};

#endif // LEVEL_H
