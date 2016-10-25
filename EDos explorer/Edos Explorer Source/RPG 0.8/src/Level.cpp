#include "Level.h"




Level::Level()
{
    //ctor
}

void Level::load(Player &user, char doorChar)   // loads and prints out level
{
    clearMap(); // clears the screen and previous map out of memory

    char levelNumberChar[3], roomNumberChar[1];
    sprintf( levelNumberChar, "%d", levelNumber );  //convert int to char
    string levelNumberString(levelNumberChar);     // char to string

    sprintf( roomNumberChar, "%d", roomNumber);
    string roomNumberString(roomNumberChar);

    string fileName = "lvl" + levelNumberString + ".txt";        // !FILE NAME!   "." + roomNumberString +     for rooms

    levelPoints = 0;

    //LOAD

    ifstream file;
    file.open(".\\maps\\" + fileName);
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
    int playerX = 0, playerY = 0;
    user.getPosition(playerX, playerY);
    for (int y = 0; y < levelMap.size(); y++)
    {
        for (int x = 0; x < levelMap[y].size(); x++)
        {

            tile = levelMap[y][x];
            switch (tile)
            {
            case userTileUp:
            case userTileDown:
            case userTileLeft:
            case userTileRight:
                if (doorChar == ' ')
                {
                    user.setPosition(x, y);
                }
                else if ( playerX != x || playerY != y)
                {
                    setTile(x, y, '.');
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
            if (doorChar == ']' && playerX != x && playerY != y )
                {
                if (!teleportUser(user, x-1, y) ) printf ("Error: unable to teleport to door. Did you forget to place the right door?");
                userTile = userTileLeft;
                }
                break;

            case ']':
                if (doorChar == '[' && playerX != x && playerY != y )
                {
                if (!teleportUser(user, x+1, y) ) printf ("Error: unable to teleport to door. Did you forget to place the right door?");
                userTile = userTileRight;
                }
                break;
            case '$':
                levelPoints++;
                break;
            }
        }
    }

    int x, y; user.getPosition (x, y); setTile(x, y, userTile);

    print();    // prints out loaded level


}
void Level::print()
{
    minWinHeight = levelMap.size() + 5;

    gotoxy(0,0);
    for (int i = 0; i < levelMap.size(); i++)   // check the max length
    {
        if ( levelMap[i].size() > minWinLength ) minWinLength = levelMap[i].size();
    }

    if ( minWinLength > 200) minWinLength = 200; //
    if ( minWinHeight > 200) minWinHeight = 200; //
    Colors::SetWindow(minWinLength + 3, minWinHeight + 8 );     //default is x=85 and y=25 length, cannot go beyond 800


    gotoxy(0,0);
    for (int i = 0; i < levelMap.size(); i++)
    {
        Colors::printStringInColor(levelMap[i]);
        cout << endl;
    }

    for (int y = 0; y < levelMap.size(); y++ )  // update everything again
    {
        for (int x = 0; x < levelMap[y].size(); x++) updateTile(x, y);
    }




    updatePoints(false);    // no sound




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

void Level::updatePoints(bool playSound) // + draw the box
{
    boxX = (minWinLength - 30) / 2;
    boxY = minWinHeight - 2;
    messageBox.setBox(boxX, boxY, 30, 5);
    messageBox.drawBox();

    gotoxy (boxX + 3, boxY + 2);
    if (levelPoints > 0)
    {
            cout << "You need " << levelPoints << " more points!" << endl;
    }
    else cout << "                        " << endl;

    if (playSound) Colors::coinSound();
}

void Level::moveUser(char input, Player &user)
{
    int PlayerX, PlayerY;
    user.getPosition(PlayerX, PlayerY);
    switch (input)
    {
    case 'w':           //up
    case 'W':
        userTile = userTileUp;
        break;
    case 's':           //down
    case 'S':
        userTile = userTileDown;
        break;
    case 'a':           //left
    case 'A':
        userTile = userTileLeft;
        break;
    case 'd':           //right
    case 'D':
        userTile = userTileRight;
        break;
    }



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
       // printf("Bad input \n");
        break;
    }
}

bool Level::tryTeleportAround (Player &user, int aroundX, int aroundY)
{
    switch (userTile)       // check preferred direction first
    {
    case userTileUp:
        if ( teleportUser(user, aroundX, aroundY-1)) goto end_function;

    case userTileDown:
        if ( teleportUser(user, aroundX, aroundY+1)) goto end_function;

    case userTileLeft:
        if ( teleportUser(user, aroundX-1, aroundY)) goto end_function;

    case userTileRight:
        if ( teleportUser(user, aroundX+1, aroundY)) goto end_function;
    }

        if (teleportUser(user, aroundX+1, aroundY) == false )
        {
            if ( teleportUser(user, aroundX-1, aroundY) == false)
            {
                if (teleportUser (user, aroundX, aroundY-1) == false)
                {
                    if (teleportUser (user, aroundX, aroundY+1) == false){
                        goto end_false;
                    }
                    else setTile (aroundX, aroundY+1, userTileDown);
                    updateTile(aroundX, aroundY+1);
                }
                 else setTile (aroundX, aroundY-1, userTileUp);
                 updateTile(aroundX, aroundY-1);
            }
            else setTile (aroundX-1, aroundY, userTileLeft);
            updateTile(aroundX-1, aroundY);
        }
        else setTile (aroundX+1, aroundY, userTileRight);
        updateTile(aroundX+1, aroundY);




    end_function:
        return true;

    end_false:
        return false;
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
        setTile(targetX, targetY, userTile);

        updateTile(playerX, playerY);
        updateTile(targetX, targetY);
        Colors::teleportSound();

        return true;            // teleport complete
    }
}

void Level::updateTile(int x, int y)
{
    Level::gotoxy(x, y);
    char tile = getTile(x, y);
    Colors::printInColor(tile);
}

void Level::nextLevelCheat(Player &user)
{
    roomNumber=0;
    levelNumber++;
    load(user, '[');
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

void Level::processPlayerMove(Player &user, int targetX, int targetY)   // process move request to tile
{
    int PlayerX, PlayerY;
    user.getPosition(PlayerX,PlayerY);
    char moveTile = getTile(targetX, targetY);

     switch (moveTile)
        {
        case '#':
            Colors::blockedSound();
            setTile(PlayerX, PlayerY, userTile);
            updateTile(PlayerX, PlayerY);
            break;

        case '.':           //air
            user.setPosition(targetX, targetY);
            setTile(PlayerX, PlayerY, '.');
            setTile(targetX, targetY, userTile);

            updateTile(PlayerX, PlayerY);
            updateTile(targetX, targetY);
            Colors::moveSound();

            break;

        case 'Q':   //teleporter
            if (targetX == teleporter1X && targetY == teleporter1Y)
            {
                targetX = teleporter2X; targetY = teleporter2Y;
                if (tryTeleportAround (user, targetX, targetY) ) goto end_loop;
            }

            else if (targetX == teleporter2X && targetY == teleporter2Y)
            {
                targetX = teleporter1X; targetY = teleporter1Y;
                if (tryTeleportAround (user, targetX, targetY) ) goto end_loop;
            }

            end_loop:
            break;

        case '$':
            user.setPosition(targetX, targetY);
            setTile(PlayerX, PlayerY, '.');
            setTile(targetX, targetY, userTile);

            updateTile(PlayerX, PlayerY);
            updateTile(targetX, targetY);
            Colors::moveSound();

            getPoint();
            updatePoints();
            break;

        case '[':           // Next level
            if (levelPoints == 0)
            {
            roomNumber=0;
            levelNumber++;
            load(user, '[');
            Colors::newLevelSound();
            }
            else Colors::blockedSound();
            break;

        case ']':           // Previous level
            roomNumber=0;
            levelNumber--;
            load(user, ']');
            Colors::newLevelSound();
            break;
        /*case '/':    // Room 1
            if (roomNumber!=1)
            {
                roomNumber = 1;

                load(user);
            }
            else
            {
                roomNumber = 0;

                load(user);
            }
            break;
        case '(':   // Room 2
        case ')':
            if (roomNumber!=2)
            {
                roomNumber = 2;

                load(user);
            }
            else
            {
                roomNumber = 0;

                load(user);
            }

            break;
        case '_':    // Room 3
            if (roomNumber!=3)
            {
                roomNumber = 3;

                load(user);
            }
            else
            {
                roomNumber = 0;

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

Level::~Level()
{
    // delete levelMap;
}
