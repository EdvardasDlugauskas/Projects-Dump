#ifndef ENGINE_H
#define ENGINE_H

#include "Player.h"
#include "Level.h"

#include <string>
#include <iostream>
#include <conio.h>  // getchar
#include <stdlib.h>

using namespace std;


class Engine
{
    public:
        Engine();

        void gameLoop();
        void userMove();
    protected:

    private:
        Player user;
        Level currentLevel;

};

#endif // ENGINE_H
