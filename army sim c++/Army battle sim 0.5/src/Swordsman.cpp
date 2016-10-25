#include "Swordsman.h"
#include "Army.h"

Swordsman::Swordsman(Army* parentArmy)
{
    setUnit(5, 1, 0, 1, 10, 10);
    setUnitChar('S');
    armyNum = parentArmy->getTeamNumber();
    setKing(parentArmy);
}

Swordsman::~Swordsman()
{
    //dtor
}
