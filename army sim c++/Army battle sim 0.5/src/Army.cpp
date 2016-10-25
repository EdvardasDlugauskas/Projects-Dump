#include "Army.h"
#include "Map2D.h"
#include "GameLoop.h"

Army::Army()
{
}

Army::Army(int team = -1, int swords = 0, int archers = 0, int horsemen=0, char direction = ' ', char type = 'B')
{
    teamNumber = team;
    sAmount = swords;
    aAmount = archers;
    hAmount = horsemen;
    armyDirection = direction;
    armyType = type;

    //! Change following:
    if (type == 'B') {discipline = 5; armyState = 0;}
    else {discipline = 10; armyState = 2;}

    createArmy();
}

Army::~Army()
{
    destroyArmy(); //not sure if needed?
}

void Army::createArmy()
{
    Units.push_back( new King(this, "King Test Jeoffrey") );
    armyKing = Units[0];

        //! UNITS CLOSEST TO THE KING IN PLACEMENT STAGE GO FIRST

    for (int i = 0; i < hAmount; ++i)
    {
        Units.push_back( new Horseman(this) );
    }

    for (int i = 0; i < sAmount; ++i )
    {
        Units.push_back( new Swordsman(this) );
    }

    for (int i = 0; i < aAmount; ++i )
    {
        Units.push_back( new Archer(this) );
    }


}

void Army::destroyArmy()
{
    for (auto it = Units.begin(); it != Units.end(); ++it){
        delete *it;
    }
    Units.clear();
}

void Army::armyMove(Map2D* battleMap, vector<Army*> armies)
{
    for (Unit* unit : Units)
    {
        unit->updateUnit(battleMap);
        if (unit->isStillAlive()) unit->unitMove(battleMap, armies);
        if (GameLoop::battleEnd) return;
    }
}
//    for (auto it = Units.begin(); it != Units.end(); ++it)
//    {
//        if ((*it)->Units)
//        (*it)->unitMove(battleMap, armies);
//    }
