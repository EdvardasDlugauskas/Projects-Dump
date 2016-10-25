#include "King.h"
#include "Army.h"

King::King(Army* parentArmy, std::string kingName)
{
    setUnit(10, 1, 0, 2, 100, 100);
    name = kingName;
    setUnitChar('K');
    armyNum = parentArmy->getTeamNumber();
    setKing(parentArmy); // for set disc and army type
}

King::~King()
{
    //dtor
}

void King::unitMove(Map2D* battleMap, vector<Army*> Armies)
{
    assignEnemy(Armies);
    //!Check if legion or barbaric
    if (armyType == 'B' || unitState == 0) barbaricMove(battleMap, Armies);
    else kingMove(battleMap, Armies);
}

void King::kingMove(Map2D* battleMap, vector<Army*> Armies)
{
    if (Pathfinding::findDistance( unitCoord, targetUnit->getUnitCoord() ) <= 1)
    {
        //! Attack!
        attackTargetUnit(battleMap);
        return;
    }
    else if (unitState == 1 || Pathfinding::findDistance(unitCoord, targetUnit->getUnitCoord()) <= 4) moveCloser(battleMap);
    else
    {
        navigateTo(battleMap, Pathfinding::findCenter(myArmy));
    }
}
