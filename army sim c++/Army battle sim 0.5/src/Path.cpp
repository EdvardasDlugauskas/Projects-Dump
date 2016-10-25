#include "Path.h"

Pathfinding::Pathfinding()
{
    m_initializedStartGoal = false;
    m_foundGoal = false;
}

Pathfinding::~Pathfinding()
{
    for(int i = 0; i < m_openList.size(); i++)
        {
            delete m_openList[i];

        }
        m_openList.clear();

        for(int i = 0; i < m_visitedList.size(); i++)
        {
            delete m_visitedList[i];
        }
        m_visitedList.clear();

        for (int i = 0; i < m_pathToGoal.size(); i++)
        {
            delete m_pathToGoal[i];
        }
        m_pathToGoal.clear();
}

vector<COORD*> Pathfinding::findPath(Map2D* thisMap, COORD currentPos, COORD targetPos)
{
    currentMap = thisMap;
    if (!m_initializedStartGoal)
    {
        for(int i = 0; i < m_openList.size(); i++)
        {
            delete m_openList[i];

        }
        m_openList.clear();

        for(int i = 0; i < m_visitedList.size(); i++)
        {
            delete m_visitedList[i];
        }
        m_visitedList.clear();

        for (int i = 0; i < m_pathToGoal.size(); i++)
        {
            delete m_pathToGoal[i];
        }
        m_pathToGoal.clear();

        // Initialize start
        SearchCell start;
        start.m_xCoord = currentPos.X;
        start.m_yCoord = currentPos.Y;

        // Initialize goal
        SearchCell goal;
        goal.m_xCoord = targetPos.X;
        goal.m_yCoord = targetPos.Y;

        setStartAndGoal(start, goal);
        m_initializedStartGoal = true;

    }

    if (m_initializedStartGoal)
    {
        {
            while (!m_foundGoal && m_isPath)
            {
                continuePath();
            }
        }
        return m_pathToGoal;

    }


}

void Pathfinding::setStartAndGoal(SearchCell start, SearchCell goal)
{
    m_startCell = new SearchCell(start.m_xCoord, start.m_yCoord, 0);
    m_goalCell = new SearchCell (goal.m_xCoord, goal.m_yCoord, &goal);

    m_startCell->G = 0;
    m_startCell->H = m_startCell->manhattanDistance(m_goalCell);
    m_startCell->parent = nullptr;

    //!mine
//    m_visitedList.push_back(m_startCell);
//    pathOpened(start.m_xCoord, start.m_yCoord, m_startCell->G + 1, m_startCell);

    m_openList.push_back(m_startCell);
}

SearchCell* Pathfinding::getNextCell()
{
    float bestF = 99999.0f;
    int cellIndex = -1;
    SearchCell* nextCell = nullptr;

    for(int i = 0; i < m_openList.size(); i++)
    {
        if (m_openList[i]->getF() < bestF)
        {
            bestF = m_openList[i]->getF();
            cellIndex = i;
        }
    }

    if (cellIndex >= 0)
    {
        nextCell = m_openList[cellIndex];
        m_visitedList.push_back(nextCell);
        m_openList.erase(m_openList.begin() + cellIndex);
    }

    return nextCell;
}

void Pathfinding::pathOpened(int x, int y, float newCost, SearchCell* parent)
{
    int id = y * WORLD_SIZE + x;
    if (id == m_goalCell->m_id) goto next_step;

    {
    COORD tileCoord = { .X = x, .Y = y };
    if ( currentMap->getTile(x, y) != ' ')   //! CELL_BLOCKED - if cell is blocked, then ignore it
    {
//         cout << currentMap->getLayerTile(tileCoord)->botLayer << "!!! " ;
        return;
    }

    if (currentMap->getLayerTile(tileCoord)->unitStationed != nullptr)
    {
        if (currentMap->getLayerTile(tileCoord)->unitStationed->isStillAlive()) return;
    }
    }

    next_step:


    for (int i = 0; i < m_visitedList.size(); i++)
    {
        if (id == m_visitedList[i]->m_id)
        {
            return;
        }
    }

    SearchCell* newChild = new SearchCell(x, y, parent);
    newChild->G = newCost;
    newChild->H = parent->manhattanDistance(m_goalCell);

    for (int i = 0; i < m_openList.size(); i++)
    {
        if (id == m_openList[i]->m_id)
        {
            float newF = newChild->G + newCost + m_openList[i]->H;

            if (m_openList[i]->getF() > newF)
            {
                m_openList[i]->G = newChild->G + newCost;
                m_openList[i]->parent = newChild;
            }
            else
            {
                delete newChild;
                return;
            }
        }
    }
    m_openList.push_back(newChild);
}

void Pathfinding::continuePath()
{
    if(m_openList.empty())
    {
        m_isPath = false;
        return;
    }

    SearchCell* currentCell = getNextCell();
    if (currentCell->m_id == m_goalCell->m_id ) //|| currentCell->manhattanDistance(m_goalCell) <= 1
    {
        m_goalCell->parent = currentCell->parent;

        SearchCell* getPath;

        for( getPath = m_goalCell; getPath != 0; getPath = getPath->parent)
        {
            COORD* newCoord = new COORD;
            newCoord->X = getPath->m_xCoord;
            newCoord->Y = getPath->m_yCoord;
            m_pathToGoal.push_back( newCoord );
        }

        m_foundGoal = true;
        return;
    }
    else
    {
        //right side
        pathOpened(currentCell->m_xCoord + 1, currentCell->m_yCoord, currentCell->G + 1, currentCell); // [G + 1] is value of cell
        //left side
        pathOpened(currentCell->m_xCoord - 1, currentCell->m_yCoord, currentCell->G + 1, currentCell);
        // up
        pathOpened(currentCell->m_xCoord, currentCell->m_yCoord + 1, currentCell->G + 1, currentCell);
        // down
        pathOpened(currentCell->m_xCoord, currentCell->m_yCoord - 1, currentCell->G + 1, currentCell);

        for (int i = 0; i < m_openList.size(); i++)
        {
            if (currentCell->m_id == m_openList[i]->m_id)
            {
                m_openList.erase(m_openList.begin() + i);
            }
        }
    }
}


int Pathfinding::findDirection(COORD pathStart, COORD pathEnd)
{
    int altitude = pathStart.Y - pathEnd.Y;

    if ( abs(pathStart.X - pathEnd.X) > abs(altitude))  // move to the side?
    {
        if (pathStart.X - pathEnd.X > 0) return 3;    // which side?
        else return 1;
    }

    else
    {
        if (altitude > 0 ) return 0;
        else if (abs(altitude) == 0 && abs(pathStart.X - pathEnd.X == 0) ) return -1; // next
        else return 2;
    }
}

Unit* Pathfinding::findEnemy(Unit* lookingUnit, vector<Army*> armies)
{
    int friendlyNum = lookingUnit->getArmyNumber();
    int closestDistance = 9999;
    Unit* closestUnit = nullptr;

    for (Army* army : armies)
    {
        if (army->Units.empty() ) continue;
        if (army->getTeamNumber() != friendlyNum)
        {
            for (Unit* unit : army->Units)
            {
                if (unit->isStillAlive())
                {
                    COORD target = unit->getUnitCoord();
                    COORD start = lookingUnit->getUnitCoord();
                    if (findDistance(start, target) < closestDistance)
                    {
                        closestDistance = findDistance(start, target);
                        lookingUnit->setTargetUnit(unit);
                    }
                }

            }
        }
    }
    if (closestDistance > 9000) return nullptr;
}

int Pathfinding::findDistance(COORD pathStart, COORD pathEnd)
{
    int altitude = abs(pathStart.Y - pathEnd.Y);
    int latitude = abs(pathStart.X - pathEnd.X);

    return altitude + latitude;
}

COORD Pathfinding::findCenter(Army* army)
{
    COORD center = {.X = 0, .Y = 0};
    int i = 0;
    for (Unit* unit : army->Units)
    {
        if (unit->isStillAlive())
        {
            center.X += unit->getUnitCoord().X;
            center.Y += unit->getUnitCoord().Y;
            i++;
        }
    }
    center.X = round(center.X/i);
    center.Y = round(center.Y/i);
    return center;
}
