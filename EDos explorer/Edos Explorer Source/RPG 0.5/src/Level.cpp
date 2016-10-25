#include "Level.h"




Level::Level()
{
    //ctor
}

void Level::load(Player &user, char doorChar)
{
    char levelNumberChar[3], roomNumberChar[1];
    sprintf( levelNumberChar, "%d", levelNumber );  //convert int to char
    string levelNumberString(levelNumberChar);     // char to string

    sprintf( roomNumberChar, "%d", roomNumber);
    string roomNumberString(roomNumberChar);

    string fileName = "level" + levelNumberString + "." + roomNumberString + ".txt";        // !FILE NAME!

    levelPoints = 0;

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
    char tile;  // for switch statement
    int teleporterCount = 0; // for teleporter counting

    for (int y = 0; y < levelMap.size(); y++)
    {
        for (int x = 0; x < levelMap[y].size(); x++)
        {
            tile = levelMap[y][x];
            switch (tile)
            {
            case '@':
                if (doorChar == ' ')
                {
                    user.setPosition(x, y);
                }
                break;

            case 'Q':
                if (teleporterCount == 0) {
                    teleporter1X = x;
                    teleporter1Y = y;
                    teleporterCount++;

                }
                else if (teleporterCount == 1){
                    teleporter2X = x;
                    teleporter2Y = y;
                    teleporterCount++;
                }
                break;
            case '[':
            if (doorChar == ']')
                {
                if ( teleportUser(user, x-1, y) == false )
                {
                    if ( teleportUser(user, x+1,y) == false)
                    {
                        if (teleportUser (user,x,y-1) == false)
                        {
                            if (teleportUser (user, x, y+1) == false){
                                cout << "Door error! Unable to teleport near door." << endl;
                                exit(0);
                            }
                            else setTile (x, y+1, '@');
                        }
                         else setTile (x, y-1, '@');
                    }
                    else setTile (x+1, y, '@');
                }
                else setTile (x-1, y, '@');
                }

                break;
            case ']':
            case '|':
                if (doorChar == '[')
                {
                if ( teleportUser(user, x-1, y) == false )
                {
                    if ( teleportUser(user, x+1,y) == false)
                    {
                        if (teleportUser (user,x,y-1) == false)
                        {
                            if (teleportUser (user, x, y+1) == false){
                                cout << "Door error! Unable to teleport near door." << endl;
                                exit(0);
                        }
                            else setTile (x, y+1, '@');
                        }
                         else setTile (x, y-1, '@');
                    }
                    else setTile (x+1, y, '@');
                }
                else setTile (x-1, y, '@');
                }
                break;
            case '$':
                levelPoints++;
                break;
            }
        }
    }
    int pointX, pointY;
    user.getPosition(pointX, pointY);
    setTile(pointX, pointY, '@');



}

void Level::gotoxy(int x, int y)    // (copy pasted) moves cursor to position x, y;
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;

    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void Level::print()
{
    //cout << string(30, '\n');
    //system("CLS");

    gotoxy(0,0);
    for (int i = 0; i < levelMap.size(); i++)
    {
        printf("%s\n", levelMap[i].c_str());
    }

    if (levelPoints > 0)
    {
            cout << "You need " << levelPoints << " more points to go further!" << endl;
    }
    else cout << "                                                 " << endl;
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
    case '.':
    case '>':
        nextLevelCheat(user);
        break;
    default:
        printf("Bad input \n");
        break;
    }
}

bool Level::teleportUser(Player &user, int targetX, int targetY)
{
    int playerX, playerY;
    user.getPosition(playerX,playerY);
    char movingToTile = getTile(targetX, targetY);
    if (movingToTile != '.')
    {
        return false;           // teleport failed!
    }
    else
    {
        user.setPosition(targetX, targetY);
        setTile(playerX, playerY, '.');
        setTile(targetX, targetY, '@');
        return true;            // teleport complete
    }
}

void Level::nextLevelCheat(Player &user)
{
    roomNumber=0;
    levelNumber++;
    clearMap();
    load(user);
}

void Level::getPoint()
{
    if (levelPoints > 0)
    {
        levelPoints--;
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
     bool result=false; // for storing results (in teleporter)

     switch (moveTile)
        {
        case '#':
            break;
        case '.':           //air
            user.setPosition(targetX, targetY);
            setTile(PlayerX, PlayerY, '.');
            setTile(targetX, targetY, '@');
            break;

        case 'Q':   //teleporter
            if (targetX == teleporter1X && targetY == teleporter1Y)
            {
            result = teleportUser (user, teleporter2X+1, teleporter2Y); // preferred position for teleporting check
            if (result == true) goto end_loop;
            result = teleportUser (user, teleporter2X-1, teleporter2Y);
            if (result == true) goto end_loop;

                for (int y = -1; y <= 1; y=y+2)
                {
                      result = teleportUser(user, teleporter2X, teleporter2Y+y);
                      if  (result == true) goto end_loop;
                }
            }
            else if (targetX == teleporter2X && targetY == teleporter2Y)
            {
            result = teleportUser (user, teleporter1X+1, teleporter1Y);
            if (result == true) goto end_loop;
            result = teleportUser (user, teleporter1X-1, teleporter1Y);
            if (result == true) goto end_loop;

                for (int y = -1; y <= 1; y=y+2)
                {
                      result = teleportUser(user, teleporter1X, teleporter1Y+y);
                      if  ( result == true) goto end_loop;

                }
            }
            end_loop:
            break;

        case '$':
            user.setPosition(targetX, targetY);
            setTile(PlayerX, PlayerY, '.');
            setTile(targetX, targetY, '@');
            getPoint();
            break;

        case '[':           // Next level
            if (levelPoints == 0)
            {
            roomNumber=0;
            levelNumber++;
            clearMap();
            load(user, '[');
            break;
            }

        case ']':           // Previous level
            if (levelPoints == 0)
            {
            roomNumber=0;
            levelNumber--;
            clearMap();
            load(user, ']');
            break;
            }
        /*case '/':    // Room 1
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

            break; */



        }
}

void Level::clearMap()
{
    levelMap.clear();
    system("CLS");
}
