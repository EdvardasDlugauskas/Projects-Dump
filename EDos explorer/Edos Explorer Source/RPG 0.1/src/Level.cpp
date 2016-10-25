#include "Level.h"
#include <fstream>


Level::Level()
{
    //ctor
}

void Level::load(string fileName, Player &user)
{
    //LOAD
    ifstream file;
    file.open(fileName);
    if (file.fail())
    {
        perror(fileName.c_str());
        exit(1);
    }

    string line;

    while (getline(file, line))
    {
        levelMap.push_back(line);
    }

    file.close();


    //PROCESS
    char tile;
    for (int i = 0; i < levelMap.size(); i++)
    {
        for (int x = 0; x < levelMap[i].size(); x++)
        {
            tile = levelMap[i][x];
            switch (tile)
            {
            case '@':
                user.setPosition(x, i);
                break;
            }
        }
    }

}

void Level::print()
{
    cout << string(50, '\n');

    for (int i = 0; i < levelMap.size(); i++)
    {
        printf("%s\n", levelMap[i].c_str());
    }
    printf("\n");
}

void Level::moveUser(char input, Player &user)
{
    int PlayerX, PlayerY;
    user.getPosition(PlayerX, PlayerY);


    switch (input)
    {
    case 'w':           //up
    case 'W':
        processPlayerMove(user, PlayerX, PlayerY - 1);

        break;
    case 's':           //down
    case 'S':
        processPlayerMove(user, PlayerX, PlayerY + 1);
        break;
    case 'a':           //left
    case 'A':
        processPlayerMove(user, PlayerX - 1, PlayerY);
        break;
    case 'd':           //right
    case 'D':
        processPlayerMove(user, PlayerX + 1, PlayerY);
        break;
    default:
        printf("Bad input \n");
        system("PAUSE");
        break;
    }
}

char Level::getTile(int x,int y)
{
    return levelMap[y][x];
}

void Level::setTile(int x, int y, char tile)
{
    levelMap[y][x] = tile;
}

void Level::processPlayerMove(Player &user, int targetX, int targetY)
{
    int PlayerX, PlayerY;
    user.getPosition(PlayerX,PlayerY);
    char moveTile = getTile(targetX, targetY);

     switch (moveTile)
        {
        case '#':
            break;
        case '.':
            user.setPosition(targetX, targetY);
            setTile(PlayerX, PlayerY, '.');
            setTile(targetX, targetY, '@');
            break;

        }
}
