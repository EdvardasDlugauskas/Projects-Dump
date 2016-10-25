#ifndef ENGINE_H
#define ENGINE_H

#include "Level.h"
#include "Player.h"

#include <string>
#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;


class Engine
{
    public:
        Engine();

        void gameLoop();
        void userMove();

    private:
        Player user;
        Level currentLevel;

};

#endif // ENGINE_H
