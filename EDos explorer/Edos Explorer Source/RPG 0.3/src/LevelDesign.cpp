#include "LevelDesign.h"

LevelDesign::LevelDesign()
{
    cout <<
}

void LevelDesign::levelLoad(string levelName)
{
    ifstream levelGet;
    levelGet.open(levelName);
    if (levelGet.is_open==false)
    {
        levelGet.open(levelName+".txt");
        if (levelGet.is_open==false)
        {
            cout << "Error opening file" << endl;
            levelLoad();
        }
    }

}
