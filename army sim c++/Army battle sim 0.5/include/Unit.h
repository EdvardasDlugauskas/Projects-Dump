#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <windows.h>
#include <memory>

//#include "Map2D.h"
//#include "Army.h"

class Map2D;    // Forward declaration. Fixes circular dependency (instead of "#include Map2D")
class Army;
class Pathfinding;
class King;

class Unit
{
    public:
        Unit();
        void setKing(Army* army);   //! + set Army type, discipline
        //! Getters and setters...
        virtual ~Unit();
         int getMeleeDmg() { return meleeDmg; }

         int getHealth() { return health; }
        void setHealth( int val) { health = val; }

        char getUnitChar() { return unitChar; }
        void setUnitChar(char val) { unitChar = val; }

        void setUnit(int MeleeDmg, int Range, int RangeDmg, int Speed, int Health, int MaxHealth);

        int getArmyNumber() { return armyNum; }
        Unit* getKing() { return myKing; }

        void setTargetUnit(Unit* newTarget) { targetUnit = newTarget;}
        Unit* getTargetUnit() { return targetUnit; }

        COORD getUnitCoord() { return unitCoord; }
        COORD* getUnitCoordP() { return &unitCoord; }
        void setUnitCoord(int x, int y);

        //! Unit movement
        virtual void unitMove(Map2D* battleMap, std::vector<Army*> Armies);
        void barbaricMove(Map2D* battleMap, std::vector<Army*> Armies);
        void legionMove(Map2D* battleMap, std::vector<Army*> Armies);
        bool moveCloser(Map2D* battleMap);  // move closer to target unit
        bool moveFurther(Map2D* battleMap);

        //! Unit status
        bool isStillAlive() { return alive; }
        void updateUnit(Map2D* battleMap);
        void getDamaged(Map2D* battleMap, int damage);



        // friend class Map2D; //! can use Map2D privates

    protected:  //! can be used by derived classes
        bool alive = true;
        bool assignEnemy(std::vector <Army*> Armies);
        std::vector<COORD*> directions;
        int checkIndex = 0;


        bool attackTargetUnit(Map2D* thisMap);   // melee attack, returns if it is successful
        int armyNum = -1, discipline = 0;
        int meleeDmg;
        int range;
        int rangeDmg;
        int speed;
        float health;
        int maxHealth;
        char unitChar = '?', armyType = 'B';
        COORD unitCoord = { .X = 0, .Y = 0};
        Unit* myKing = nullptr;
        Unit* targetUnit = nullptr;
        Army* myArmy = nullptr;
        std::unique_ptr<Pathfinding> pather;
        virtual void rangedAttack(Map2D* battleMap, COORD atxy, int damage);
        void navigateTo(Map2D* battleMap, COORD targetCoord);
        int unitState = 0;

};

#endif // UNIT_H
