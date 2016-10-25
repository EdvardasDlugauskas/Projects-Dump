#include <iostream>
#include <windows.h>

#include "Player.h"
#include "Engine.h"

using namespace std;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
    ShowConsoleCursor(false);   //no flashing cursor



    Engine gameSystem;
    gameSystem.gameLoop();

}
