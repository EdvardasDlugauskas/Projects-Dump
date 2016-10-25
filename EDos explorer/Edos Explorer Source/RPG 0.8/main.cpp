#include <iostream>
#include <thread>
#include <windows.h>

#include "Player.h"
#include "Engine.h"
#include "Colors.h"

using namespace std;



int main()
{
    //Colors::SetWindow(200, 75);
    //MessageBox(NULL, "Stuff", "Inventory", MB_OK);

    Colors::ShowConsoleCursor(false);   //no flashing cursor
    Colors::defaultColors ();

                //INTRO
    cout << endl << endl <<"        EDO STUDIOS PRESENTS" << endl <<"           A GAME BY EDO" ;
    Colors::soundPlay(".\\sounds\\intro.wav");

    Engine gameSystem;
    gameSystem.gameLoop();

}
