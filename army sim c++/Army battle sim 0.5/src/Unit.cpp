#include "Unit.h"
#include "Army.h"
#include "Map2D.h"
#include "Path.h"
#include "GameLoop.h"

Unit::Unit()
{

}

void Unit::setKing(Army* army)
{
    myArmy = army;
    if (unitChar == 'K') myKing = this;
    else myKing = myArmy->armyKing;
    armyType = army->getArmyType();
    discipline = army->getDiscipline();
    unitState = army->armyState;
}

Unit::~Unit()
{
    for (COORD* dr : directions)
    {
        delete dr;
    }
    directions.clear();
}

void Unit::setUnit(int MeleeDmg = 1, int Range = 0, int RangeDmg = 0, int Speed = 1, int Health = 0, int MaxHealth = 5)
{
    meleeDmg = MeleeDmg;
    range = Range;
    rangeDmg = RangeDmg;
    speed = Speed;
    health = Health;
    maxHealth = MaxHealth;
}

void Unit::setUnitCoord(int x, int y)
{
    unitCoord.X = x;
    unitCoord.Y = y;
}

void Unit::updateUnit(Map2D* battleMap)
{
    if (health <= 0)
    {
        alive = false;
//        battleMap->getLayerTile(unitCoord)->unitStationed = nullptr;
    }
    battleMap->updateTile(&unitCoord);
    unitState = myArmy->armyState;

}

bool Unit::assignEnemy(vector <Army*> Armies)
{
    //! Barbaric movement
    pather = std::unique_ptr<Pathfinding>(new Pathfinding());
    if (Pathfinding::findEnemy(this, Armies) == nullptr)
    {
        Colors::setPrintColor(armyNum);
        cout << " VICTORY !!!!" << endl;
        cout << " TEAM " << armyNum+1 << " WINS!!!" << endl;
        cin.ignore();
        system("PAUSE");
        Colors::defaultColors();
        system("CLS");
        GameLoop::battleEnd = true;
        return false;
    }
    return true;
}

void Unit::unitMove(Map2D* battleMap, vector<Army*> Armies)
{

    if (!assignEnemy(Armies)) return;

    //!Check if legion or barbaric
    if (armyType == 'B' || unitState == 0) barbaricMove(battleMap, Armies);
    else legionMove(battleMap, Armies);

}

void Unit::barbaricMove(Map2D* battleMap, vector<Army*> Armies)
{
    if (Pathfinding::findDistance( unitCoord, targetUnit->getUnitCoord() ) <= 1)
    {
        //! Attack!
        attackTargetUnit(battleMap);
        return;
    }
    else if (Pathfinding::findDistance( unitCoord, targetUnit->getUnitCoord() ) <= range)
    {
        rangedAttack(battleMap, targetUnit->getUnitCoord(), rangeDmg);
    }
    else
    {
        //! Move closer to the enemy
        if (!moveCloser(battleMap)); // do something else...
        return;
    }
}

void Unit::legionMove(Map2D* battleMap, vector<Army*> Armies)
{
    if (Pathfinding::findDistance( unitCoord, targetUnit->getUnitCoord() ) <= 1)
    {
        //! Attack!
        attackTargetUnit(battleMap);
        return;
    }
    else if (Pathfinding::findDistance( unitCoord, targetUnit->getUnitCoord() ) <= range)
    {
        rangedAttack(battleMap, targetUnit->getUnitCoord(), rangeDmg);
    }
    else if ( Pathfinding::findDistance(unitCoord, targetUnit->getUnitCoord() ) <= (speed*5 + round(20/(discipline+1))) || unitState == 1)
    {
        //! Move closer to the enemy
        if (!moveCloser(battleMap)); // do something else...
    }
    else
    {
//        if (unitState == 1) moveCloser(battleMap);
//        else return;
    }
}

bool Unit::attackTargetUnit(Map2D* thisMap)
{
    targetUnit->getDamaged(thisMap, meleeDmg + Colors::getRNG(-meleeDmg*0.1, 0.1*meleeDmg));
    targetUnit->updateUnit(thisMap);
    myArmy->armyState = 1;
    return true;
}

void Unit::getDamaged(Map2D* battleMap, int damage)
{
    if (!this) return;
    if (myKing->isStillAlive())
    {
        if (Pathfinding::findDistance(unitCoord, myKing->getUnitCoord()) < 13) damage = damage - damage*0.2;
    }
    health -= damage;
    updateUnit(battleMap);
    myArmy->armyState = 1;
}

bool Unit::moveCloser(Map2D* battleMap)
{
    directions = pather->findPath(battleMap, unitCoord, targetUnit->getUnitCoord() );
    if (directions.size() <= 1) return false;
    else
    {
        directions.pop_back();
        for (int i = 0; i < speed; i++)
        {
            if ( Pathfinding::findDistance(unitCoord, targetUnit->getUnitCoord()) <= 1 ) return true;
            if (!battleMap->moveUnitTo(this, *directions.back()) )
                {
                    return false;
                    //! Debugging...
                }
            directions.pop_back();
        }

        return true;

    }
}

bool Unit::moveFurther(Map2D* battleMap)
{
    directions = pather->findPath(battleMap, unitCoord, targetUnit->getUnitCoord() );
    if (directions.size() == 0) return false;
    directions.pop_back();
    COORD moveCoord;
    moveCoord.X = unitCoord.X - (directions.back()->X - unitCoord.X);
    moveCoord.Y = unitCoord.Y - (directions.back()->Y - unitCoord.Y);
    if (!battleMap->moveUnitTo(this, moveCoord)) return false;
    else return true;
}

void Unit::rangedAttack(Map2D* battleMap, COORD atxy, int damage)
{
    if (battleMap->getLayerTile(atxy)->unitStationed) battleMap->getLayerTile(atxy)->unitStationed->getDamaged(battleMap, rangeDmg+Colors::getRNG(-0.1*rangeDmg, 0.1*rangeDmg));
}

void Unit::navigateTo(Map2D* battleMap, COORD targetCoord)
{
    directions = pather->findPath(battleMap, unitCoord, targetCoord);
    if (directions.size() <= 1) return;
    else
    {
        directions.pop_back();
        for (int i = 0; i < speed; i++)
        {
            if ( Pathfinding::findDistance(unitCoord, targetCoord) <= 1 ) return;
            if (!battleMap->moveUnitTo(this, *directions.back()) )
                {
                    return;
                    //! Debugging...
                }
            directions.pop_back();
        }

    }
}
