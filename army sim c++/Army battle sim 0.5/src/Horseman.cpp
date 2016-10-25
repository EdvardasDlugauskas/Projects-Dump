#include "Horseman.h"

Horseman::Horseman(Army* parentArmy)
{
    setUnit(7, 1, 0, 2, 8, 8);
    setUnitChar('H');
    armyNum = parentArmy->getTeamNumber();
    setKing(parentArmy);
}
