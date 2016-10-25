#include <iostream>

#include "Player.h"
#include "Engine.h"

using namespace std;

int main()
{
    Engine gameSystem("level1.txt");

    gameSystem.gameLoop();

}
