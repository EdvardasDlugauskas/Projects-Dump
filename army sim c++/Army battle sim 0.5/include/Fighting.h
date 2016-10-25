#ifndef FIGHTING_H
#define FIGHTING_H
#include <iostream>

#include "Map2D.h"


using namespace std;

class Fighting
{
    public:
        Fighting();
        virtual ~Fighting();

        static void fight(); // game loop
};

#endif // FIGHTING_H
