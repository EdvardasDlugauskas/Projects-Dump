#ifndef TELEPORT_H
#define TELEPORT_H

#include "Level.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Teleport
{
    public:
        Teleport();

        bool teleportUser(Player &user, int targetX, int targetY);  // tries teleporting user to a tile, false if failed
        bool tryTeleportAround (Player &user, int aroundX, int aroundY);
        int teleporter1X,teleporter1Y, teleporter2X,teleporter2Y;   // for teleporters on map

    protected:
    private:
};

#endif // TELEPORT_H
