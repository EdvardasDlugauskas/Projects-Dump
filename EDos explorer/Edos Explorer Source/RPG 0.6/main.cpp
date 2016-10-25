#include <iostream>
#include <windows.h>

#include "Player.h"
#include "Engine.h"
#include "Colors.h"

using namespace std;



int main()
{
    Colors::ShowConsoleCursor(false);   //no flashing cursor
    Colors::defaultColors ();

    Engine gameSystem;
    gameSystem.gameLoop();

}
