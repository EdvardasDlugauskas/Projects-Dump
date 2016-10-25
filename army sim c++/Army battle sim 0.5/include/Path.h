#ifndef PATH_H
#define PATH_H

#include <vector>
#include <math.h>
#include <iostream>
#include <windows.h>
#define WORLD_SIZE 35

#include "Map2D.h"
#include "Unit.h"
#include "Army.h"

using namespace std;

struct SearchCell
    {
        int m_xCoord, m_yCoord;
        int m_id;   // the Cell's number
        SearchCell* parent;
        float G, H; // G - distance from start, H - distance to goal
        SearchCell()
        {
            parent = 0;
        }

        SearchCell (int x, int y, SearchCell* _parent)
        {
            m_xCoord = x;
            m_yCoord = y;
            parent = _parent;
            m_id = y * WORLD_SIZE + x;
            G = 0;
            H = 0;
        }

        float getF() { return G + H; }
        float manhattanDistance(SearchCell* nodeEnd)
        {
            float x = (fabs(this->m_xCoord - nodeEnd->m_xCoord));
            float y = (fabs(this->m_yCoord - nodeEnd->m_yCoord));

            return x + y;
        }

    };

class Pathfinding
{
    public:
        Pathfinding();
        virtual ~Pathfinding();

        vector<COORD*> findPath(Map2D* thisMap, COORD currentPos, COORD targetPos);
//        Vector3 nextPathPos();
        void clearOpenList() { m_openList.clear(); }
        void clearVisitedList() { m_visitedList.clear(); }
        void clearPathToGoal() { m_pathToGoal.clear(); }
        bool m_initializedStartGoal, m_foundGoal, m_isPath = true;

        static Unit* findEnemy(Unit* lookingUnit, vector<Army*> armies);
        static int findDistance(COORD pathStart, COORD pathEnd);
        static int findDirection(COORD pathStart, COORD pathEnd);
        static COORD findCenter(Army* army);

    private:
        void setStartAndGoal(SearchCell start, SearchCell goal);
        void pathOpened(int x, int y, float newCost, SearchCell* parent);
        SearchCell* getNextCell();
        vector<COORD*> m_pathToGoal;
        void continuePath();
        SearchCell* m_startCell;
        SearchCell* m_goalCell;

        Map2D* currentMap = nullptr;

//        short WORLD_SIZE = 0;

        vector<SearchCell*> m_openList;
        vector<SearchCell*> m_visitedList;

};


#endif // PATH_H
