#include "Level.h"




Level::Level()
{
    //ctor
}

void Level::load(Player &user)
{
    char levelNumberChar[3], roomNumberChar[1];
    sprintf( levelNumberChar, "%d", levelNumber );  //convert int to char
    string levelNumberString(levelNumberChar);     // char to string

    sprintf( roomNumberChar, "%d", roomNumber);
    string roomNumberString(roomNumberChar);

    string fileName = "level" + levelNumberString + "." + roomNumberString + ".txt";        // !FILE NAME!

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
                bool wereBefore = false;

                for (int a = 0; a < levelSaves.size(); a++)       // Load previous position (if you were there before)
                {
                    if (levelSaves(a).levelName == fileName)
                    {
                        wereBefore = true;
                        setTile(x, i, '.');
                        user.setPosition( levelSaves(a).xCoordinate, levelSaves(a).yCoordinate );
                        setTile( levelSaves(a).xCoordinate, levelSaves(a).yCoordinate, '@' );
                        break;
                    }
                }

                if (wereBefore==false){
                        user.setPosition(x, i);
                        break;
                                    }
                else break;
            }
        }
    }



}

void Level::print()
{
    cout << string(30, '\n');

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
        case '.':           //air
            user.setPosition(targetX, targetY);
            setTile(PlayerX, PlayerY, '.');
            setTile(targetX, targetY, '@');
            break;
        case '[':           // Next level
            roomNumber=0;
            levelNumber++;
            clearMap();
            load(user);
            break;
        case ']':           // Previous level
            roomNumber=0;
            levelNumber--;
            clearMap();
            load(user);
            break;
        case '/':    // Room 1
            if (roomNumber!=1)
            {
                roomNumber = 1;
                clearMap();
                load(user);
            }
            else
            {
                roomNumber = 0;
                clearMap();
                load(user);
            }
            break;
        case '(':   // Room 2
        case ')':
            if (roomNumber!=2)
            {
                roomNumber = 2;
                clearMap();
                load(user);
            }
            else
            {
                roomNumber = 0;
                clearMap();
                load(user);
            }

            break;
        case '_':    // Room 3
            if (roomNumber!=3)
            {
                roomNumber = 3;
                clearMap();
                load(user);
            }
            else
            {
                roomNumber = 0;
                clearMap();
                load(user);
            }

            break;



        }
}

void Level::clearMap()
{
    levelMap.clear();
}
