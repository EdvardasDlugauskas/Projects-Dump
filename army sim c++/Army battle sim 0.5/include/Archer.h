#ifndef ARCHER_H
#define ARCHER_H

#include <Unit.h>
#include <Map2D.h>
#include <Path.h>
#include <Army.h>


class Archer : public Unit
{
    public:
        Archer( Army* parentArmy);
        virtual ~Archer();
        void rangedAttack(Map2D* battleMap, COORD atxy, int damage);
};

#endif // ARCHER_H
