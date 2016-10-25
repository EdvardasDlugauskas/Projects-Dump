#ifndef SWORDSMAN_H
#define SWORDSMAN_H

#include <Unit.h>


class Swordsman : public Unit
{
    public:
        Swordsman(Army* parentArmy);
        virtual ~Swordsman();
    protected:
    private:
};

#endif // SWORDSMAN_H
