#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Colors.h"
#include "Box.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h> // Goto X,Y ; SetConsoleTextAttribute

using namespace std;


class Level
{
    public:
        Level();
        ~Level();

        void load(Player &user, char doorChar = ' ');
        void print();
        void moveUser(char input, Player &user);

        const static char userTileUp = '^', userTileDown = 'v', userTileLeft = '<', userTileRight = '>';
        char userTile = '>';
        char getTile(int x, int y);
        void setTile(int x, int y, char tile);
        void getPoint();
        void nextLevelCheat(Player &user);

        void updateTile(int x, int y);
        bool teleportUser(Player &user, int targetX, int targetY);  // tries teleporting user to a tile, false if failed
        bool tryTeleportAround (Player &user, int aroundX, int aroundY);
        int teleporter1X,teleporter1Y, teleporter2X,teleporter2Y;   // for teleporters on map

        void gotoxy(int x, int y);  // move cursor for printing
        vector <string> levelMap;

    protected:


    private:

        Box messageBox;
        int boxX = 0, boxY = 0;
        int minWinLength = 50, minWinHeight = 25;

        int levelNumber=1, roomNumber=0; // Ex. lvl1.0;

        int levelPoints = 0;    // for collecting '$'

        void processPlayerMove(Player &user, int targetX, int targetY);

        void clearMap();

        void updatePoints(bool playSound = true);


};

#endif // LEVEL_H
