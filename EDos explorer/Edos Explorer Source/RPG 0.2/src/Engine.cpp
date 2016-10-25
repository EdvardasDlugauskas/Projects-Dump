#include "Engine.h"

Engine::Engine()    //constructor
{
    user.initialize(1, 100, 10, 10, 0);

    currentLevel.load(user);
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
    input = _getch();

    currentLevel.moveUser(input, user);

}
