#include "Archer.h"
#include "Army.h"

Archer::Archer(Army* parentArmy)
{
    setUnit(2, 5, 1, 1, 5, 5);
    setUnitChar('A');
    armyNum = parentArmy->getTeamNumber();
    setKing(parentArmy);
}

Archer::~Archer()
{
    //dtor
}

void Archer::rangedAttack(Map2D* battleMap, COORD atxy, int damage)
{
    if (Pathfinding::findDistance(unitCoord, atxy) <= 2 && armyType == 'L')
    {
        //! Run away
        if (moveFurther(battleMap)) return;
    }
    else if (battleMap->getLayerTile(atxy)->unitStationed) battleMap->getLayerTile(atxy)->unitStationed->getDamaged(battleMap, damage);
}
