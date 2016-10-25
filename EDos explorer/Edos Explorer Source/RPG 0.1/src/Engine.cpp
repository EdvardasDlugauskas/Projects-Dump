#include "Engine.h"

Engine::Engine(string levelFile)    //constructor
{
    user.initialize(1, 100, 10, 10, 0);

    currentLevel.load(levelFile, user);
}

void Engine::gameLoop()
{
    bool isDone = false;

    while (isDone == false)
    {
            currentLevel.print();
            userMove();
    }
}

void Engine::userMove()
{
    char input;
    cout << "Move (w/a/s/d): ";
    input = _getch();

    currentLevel.moveUser(input, user);

}
