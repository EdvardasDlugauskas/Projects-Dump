#include "Map2D.h"
#include "Army.h"
#include <algorithm>

void Map2D::loadMap(string levelMapName)
{
    layers.clear();

    mapName = levelMapName;

    //LOADING

    ifstream file;
    file.open(mapName);
    if (file.fail())
    {
        perror(mapName.c_str());
        exit(1);
    }



    string line;
    tile temp;
    vector<tile> tempVec;
    int Y = 0, X = 0;
    while (getline(file, line))
    {
        temp.Y = Y;

        X = 0;
        for (char chr : line)
        {
            temp.X = X;
            temp.botLayer = chr;
            temp.upLayer = ' ';
            temp.unitStationed = nullptr;
            tempVec.push_back(temp);
            X++;
        }
        if (line.size() > mapWidth) mapWidth = line.size();

        layers.push_back(tempVec);
        tempVec.clear();
        Y++;
    }
    file.close();
    mapHeight = layers.size();


    //PROCESSING

        //SET ARMY CENTER POINTS
    armyCoord[0].X = mapWidth / 2;
    armyCoord[0].Y = mapHeight - 5;

    armyCoord[1].X = mapWidth / 2;
    armyCoord[1].Y = 6; // 3-1 because coordinates in CMD

    armyCoord[2].Y = mapHeight / 2;
    armyCoord[2].X = 6;

    armyCoord[3].Y = mapHeight / 2;
    armyCoord[3].X = mapWidth - 5;
}

void Map2D::printMap()
{
    system("CLS");

    for (int i = 0; i < layers.size(); i++)
    {
        for (int j = 0; j < layers[i].size(); j++)
        {
            Colors::gotoxy(j, i);
            if (layers[i][j].unitStationed != nullptr)
            {
                if (layers[i][j].unitStationed->isStillAlive()) Colors::printUnitColor(layers[i][j].unitStationed);
                else layers[i][j].unitStationed = nullptr;
            }
            else if ( layers[i][j].upLayer != ' ') cout << layers[i][j].upLayer;
            else cout << layers[i][j].botLayer;
        }
        cout << endl;
    }
    printf("\n");

    Colors::setWindowSize(mapWidth+2, mapHeight+3);

}

void Map2D::updateTile(COORD* tileCoord)
{
    short x = tileCoord->X, y = tileCoord->Y;
    Colors::gotoxy(x, y);
    if (layers[y][x].unitStationed != nullptr)
    {
        if (layers[y][x].unitStationed->isStillAlive()) Colors::printUnitColor(layers[y][x].unitStationed);
        else layers[y][x].unitStationed = nullptr;
    }
    else if ( layers[y][x].upLayer != ' ') cout << layers[y][x].upLayer;
    else cout << layers[y][x].botLayer;
}

void Map2D::placeArmies( vector<Army *> armies )    // unfinished???
{
        //! WILL HANDLE PLACING ARMIES ACCORDING TO DISCIPLINE

    for (Army* army : armies)
    {
        switch(army->getArmyType())
        {
        case 'B':
            placeBarbaricArmies(army);
            break;
        case 'L':
            placeLegion(army);
            break;
        }
    }
}

void Map2D::placeBarbaricArmies(Army* army)
{
    int armyNumber = army->getTeamNumber();
    int discipline = army->getDiscipline();

    if (discipline <= 5) std::random_shuffle(army->Units.begin()+1, army->Units.end());  //!Shuffle for random placement, KING is still first

    char direction = army->armyDirection;

    placeUnit( army->Units[0], armyCoord[armyNumber] );    // place King

       // for switch loops
    COORD placingCoord = armyCoord[armyNumber];
    int i = 1;  // unit iterator
    int line = 0, place;
    int // variable defaults, change in switch() according to direction!
    xLineChange = 0,    // Spaces between unit lines on Y axis
     yLineChange = 0,   // . . . on X axis (only one should be changed)
      xPlaceChange = 0,     // Spaces between units themselves on the X axis    (negative numbers change symmetry)
       yPlaceChange = 0,    // . . . on Y axis (only one should be changed)
        maxLineWidth = 1;

    switch (direction){

    case 'W':
        yLineChange = -1;
        xPlaceChange = 1;
        maxLineWidth = mapWidth / (4 * abs(xPlaceChange)) + 1;  // *placeChange because it calculates based on place, not on location (see while loop below)
        break;

    case 'S':
        yLineChange = 1;
        xPlaceChange = 1;
        maxLineWidth = mapWidth / (4 * abs(xPlaceChange)) + 1;
        break;

    case 'A':
        xLineChange = 1;
        yPlaceChange = 1;
        maxLineWidth = mapHeight / (4 * abs(yPlaceChange)) + 1;
        break;

    case 'D':
        xLineChange = -1;
        yPlaceChange = 1;
        maxLineWidth = mapHeight / (4 * abs(yPlaceChange)) + 1;
        break;

    }

    while (true)
        {
            // ROWS
            place = 0;
            line++;
            if (xLineChange != 0) placingCoord.X = armyCoord[armyNumber].X + line * xLineChange;   // DIRECTION
            if (yLineChange != 0) placingCoord.Y = armyCoord[armyNumber].Y + line * yLineChange;
            if (xPlaceChange != 0) placingCoord.X = armyCoord[armyNumber].X + place * xPlaceChange;
            if (yPlaceChange != 0) placingCoord.Y = armyCoord[armyNumber].Y + place * yPlaceChange;
            //if (getTile(placingCoord.X, placingCoord.Y) == ' ') placeUnit(army->Units[i], placingCoord); i++;

            for (; place < maxLineWidth; place++ )
            {
                if (Colors::getRNG(0, discipline) < 4) continue;    //! Randomize placement a bit
                // COLUMNS
                if ( i == army->Units.size() ) goto end_loop;

                if (xPlaceChange != 0) placingCoord.X = armyCoord[armyNumber].X + place * xPlaceChange; //DIRECTION
                if (yPlaceChange != 0) placingCoord.Y = armyCoord[armyNumber].Y + place * yPlaceChange;

                if ( getTile(placingCoord.X, placingCoord.Y) == ' ' && layers[placingCoord.Y][placingCoord.X].unitStationed == nullptr)
                {
                    placeUnit( army->Units[i], placingCoord);
                    i++; // "next unit!"
                    if ( i == army->Units.size() ) goto end_loop;
                }

                if (xPlaceChange != 0) placingCoord.X = armyCoord[armyNumber].X - place * xPlaceChange;   //DIRECTION
				if (yPlaceChange != 0) placingCoord.Y = armyCoord[armyNumber].Y - place * yPlaceChange;

                if ( getTile(placingCoord.X, placingCoord.Y) == ' ' && layers[placingCoord.Y][placingCoord.X].unitStationed == nullptr)
                {
                    placeUnit( army->Units[i], placingCoord);
                    i++; // "next unit!"
                    if ( i == army->Units.size() ) goto end_loop;
                }
            }
        }
        end_loop:
            ;
}

void Map2D::placeLegion(Army* army)
{
    int armyNumber = army->getTeamNumber();
    int discipline = army->getDiscipline();
    char direction = army->armyDirection;

    placeUnit( army->Units[0], armyCoord[armyNumber] );    // place King

       // for switch loops
    COORD placingCoord = armyCoord[armyNumber];
    int i = 1;  // unit iterator
    int line = 0, place;
    int // variable defaults, change in switch() according to direction!
    xLineChange = 0,    // Spaces between unit lines on Y axis
     yLineChange = 0,   // . . . on X axis (only one should be changed)
      xPlaceChange = 0,     // Spaces between units themselves on the X axis    (negative numbers change symmetry)
       yPlaceChange = 0,    // . . . on Y axis (only one should be changed)
        maxLineWidth = 1;

    switch (direction){

    case 'W':
        yLineChange = -1;
        xPlaceChange = 2;
        maxLineWidth = mapWidth / (4 * abs(xPlaceChange)) + 1;  // *placeChange because it calculates based on place, not on location (see while loop below)
        break;

    case 'S':
        yLineChange = 1;
        xPlaceChange = 2;
        maxLineWidth = mapWidth / (4 * abs(xPlaceChange)) + 1;
        break;

    case 'A':
        xLineChange = 1;
        yPlaceChange = 2;
        maxLineWidth = mapHeight / (4 * abs(yPlaceChange)) + 1;
        break;

    case 'D':
        xLineChange = -1;
        yPlaceChange = 2;
        maxLineWidth = mapHeight / (4 * abs(yPlaceChange)) + 1;
        break;

    }

    while (true)
        {
            xPlaceChange*=-1; yPlaceChange*=-1;
            char curUnit = army->Units[i]->getUnitChar();
            if (curUnit == 'H') line--; // place near king
            // ROWS
            place = 0;
            line++;
            if (xLineChange != 0) placingCoord.X = armyCoord[armyNumber].X + line * xLineChange;   // DIRECTION
            if (yLineChange != 0) placingCoord.Y = armyCoord[armyNumber].Y + line * yLineChange;
            if (xPlaceChange != 0) placingCoord.X = armyCoord[armyNumber].X + place * xPlaceChange;
            if (yPlaceChange != 0) placingCoord.Y = armyCoord[armyNumber].Y + place * yPlaceChange;

            for (; place < maxLineWidth; place++ )
            {
                curUnit = army->Units[i]->getUnitChar();
                // COLUMNS
                if ( i == army->Units.size() ) goto end_loop;

                if (xPlaceChange != 0) placingCoord.X = armyCoord[armyNumber].X + place * xPlaceChange; //DIRECTION
                if (yPlaceChange != 0) placingCoord.Y = armyCoord[armyNumber].Y + place * yPlaceChange;

                if ( getTile(placingCoord.X, placingCoord.Y) == ' ' && layers[placingCoord.Y][placingCoord.X].unitStationed == nullptr)
                {
                    placeUnit( army->Units[i], placingCoord);
                    i++; // "next unit!"
                    if ( i == army->Units.size() ) goto end_loop;
                }
                if (curUnit != army->Units[i]->getUnitChar()) goto end_for;

                if (xPlaceChange != 0) placingCoord.X = armyCoord[armyNumber].X - place * xPlaceChange;   //DIRECTION
				if (yPlaceChange != 0) placingCoord.Y = armyCoord[armyNumber].Y - place * yPlaceChange;

                if ( getTile(placingCoord.X, placingCoord.Y) == ' ' && layers[placingCoord.Y][placingCoord.X].unitStationed == nullptr)
                {
                    placeUnit( army->Units[i], placingCoord);
                    i++; // "next unit!"
                    if ( i == army->Units.size() ) goto end_loop;
                }
                if (curUnit != army->Units[i]->getUnitChar()) goto end_for;
            }
            end_for:
                ;
        }
        end_loop:
            ;
//    std::reverse(army->Units.begin(), army->Units.end());
}

void Map2D::placeUnit (Unit* placedUnit, COORD placeTile)
{
    placedUnit->setUnitCoord( placeTile.X, placeTile.Y );
    layers[placeTile.Y][placeTile.X].unitStationed = placedUnit;
//    layers[placeTile.Y][placeTile.X].upLayer = placedUnit->getUnitChar();
    updateTile(&placeTile);
}

bool Map2D::moveUnit(Unit* movedUnit, int direction)  //!Tries to move, else returns false
{
    COORD moveTile = movedUnit->getUnitCoord();

    switch(direction)
    {
        case 0:
            moveTile.Y = movedUnit->getUnitCoord().Y - 1;
            break;
        case 1:
            moveTile.X = movedUnit->getUnitCoord().X + 1;
            break;
        case 2:
            moveTile.Y = movedUnit->getUnitCoord().Y + 1;
            break;
        case 3:
            moveTile.X = movedUnit->getUnitCoord().X - 1;
            break;
    }

    if ( getTile(moveTile.X, moveTile.Y) != ' ' || layers[moveTile.Y][moveTile.X].unitStationed != nullptr) return false;

    else
    {
        //! Remove from previous tile
        COORD temp = movedUnit->getUnitCoord();
        layers[temp.Y][temp.X].unitStationed = nullptr;
        updateTile(movedUnit->getUnitCoordP());
//        layers[temp.Y][temp.X].upLayer = ' ';
        //! Add to next tile
        placeUnit(movedUnit, moveTile);
        return true;
    }
}

bool Map2D::moveUnitTo(Unit* movedUnit, COORD placingCoord)
{
    if ( getTile(placingCoord.X, placingCoord.Y) != ' ' ) return false; //|| layers[placingCoord.Y][placingCoord.X].unitStationed != nullptr
    else
    {
        //! Remove
        layers[movedUnit->getUnitCoord().Y][movedUnit->getUnitCoord().X].unitStationed = nullptr;
//        layers[movedUnit->getUnitCoord().Y][movedUnit->getUnitCoord().X].upLayer = ' ';
        updateTile(movedUnit->getUnitCoordP());
        //! Place
        placeUnit(movedUnit, placingCoord);
        return true;
    }

}

char Map2D::getTile(int x, int y)
{
    if (layers[y][x].upLayer != ' ') return layers[y][x].upLayer;
    else return layers[y][x].botLayer;

}

void Map2D::setUpTile(int x, int y, char tileChar)
{
    layers[y][x].upLayer = tileChar;
}
