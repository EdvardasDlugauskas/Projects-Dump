#include "Engine.h"

Engine::Engine()    //constructor
{
    user.initialize();

    currentLevel.load(user);   // because currentLevel is a pointer
}

void Engine::gameLoop()
{
    bool isDone = false;

    while (isDone == false)
    {
            userMove();
    }
}

void Engine::userMove()
{
    char input;
    input = _getch();

    currentLevel.moveUser(input, user);

}
