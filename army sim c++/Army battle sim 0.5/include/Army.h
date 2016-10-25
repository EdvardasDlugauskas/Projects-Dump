#ifndef ARMY_H
#define ARMY_H

#include <vector>
#include <string>
#include <algorithm>

#include "Unit.h"
#include "Swordsman.h"
#include "Archer.h"
#include "King.h"
#include "Horseman.h"

class Map2D;    // Forward declaration. Fixes circular dependency (instead of "#include Map2D")
using namespace std;


class Army
{
    public:
        Army();
        Army(int team, int swords, int archers, int horsemen, char direction, char type);
        virtual ~Army();
        void armyMove(Map2D* battleMap, vector<Army*> armies);
        vector<Unit*> Units;
        char armyDirection;

        int getTeamNumber() { return teamNumber; }
        int getDiscipline() { return discipline; }
        char getArmyType() { return armyType; }
        int armyState = 0; // FREE, ATTACK, HOLD
        Unit* armyKing = nullptr;


    private:


        int teamNumber;
        int sAmount, aAmount, hAmount, armySize;    //swords and archers
        string generalName = "General name not set in Army";
        char armyType;

        void createArmy();


        int morale, discipline; // whatever...

        void destroyArmy();

};

#endif // ARMY_H
