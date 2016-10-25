#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <vector>
#include <memory>
#include <thread>

#include "Map2D.h"
#include "Army.h"
#include "Colors.h"
#include "Path.h"
#include "Unit.h"

using namespace std;

class GameLoop
{
    public:
        GameLoop();
        void play();
        static bool battleEnd;
        enum gameState
        {
            MainMenu,
            ArmyMaking,
            BattleMap
        }currentState;
        void battleMap();
        void mainMenu();
        void armyMaking();

    private:
        vector<Army*> customArmies;
        unique_ptr<Map2D> battle = unique_ptr<Map2D>(new Map2D());
};

#endif // GAMELOOP_H
