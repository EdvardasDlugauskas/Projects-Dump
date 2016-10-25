#include "GameLoop.h"
#include <conio.h>

bool GameLoop::battleEnd;

GameLoop::GameLoop()
{
    currentState = MainMenu;
    Colors::ShowConsoleCursor(false);
    Colors::initRNG();
}

void GameLoop::play()
{
    while(true)
    {
        if (currentState == BattleMap) battleMap();
        else if (currentState == MainMenu) mainMenu();
        else if (currentState == ArmyMaking) armyMaking();
    }

}

void GameLoop::battleMap()
{
    //!Setup
    battle->loadMap("defaultmap2.txt");
//    vector<Army*> Armies;  // should push back armies with "new"
//    Army userArmy(0, 15, 7, 5, 'W', 'L'); // team, swords, archers, horsemen, direction, type barbaric/legion (B/L)
//    Armies.push_back(&userArmy);
//    Army enemyArmy(1, 20, 10, 5, 'S', 'B');
//    Armies.push_back(&enemyArmy);
////    Army enemyArmy2(2, 10, 0, 'A', 'B');
////    Armies.push_back(&enemyArmy2);
////    Army enemyArmy3(3, 10, 1, 'D', 'B');
////    Armies.push_back(&enemyArmy3);

    battle->placeArmies(customArmies);
    battle->printMap();

    battleEnd = false;

    while (!battleEnd)    //!Game loop
    {
        getch();

        for (auto it = customArmies.begin(); it != customArmies.end(); it++)
        {
            (*it)->armyMove(battle.get(), customArmies);
        }
    }

    for (auto it = customArmies.begin(); it != customArmies.end(); ++it){
        delete *it;
    }

    customArmies.clear();

    currentState = MainMenu;
}

void GameLoop::mainMenu()
{
    char input;
    Colors::gotoxy(20, 10);
    cout << "This is the main menu, press 'Y' to play." << endl;
    cin >> input;

    if (input == 'y' || input == 'Y')  currentState = ArmyMaking;
}

void GameLoop::armyMaking()
{
    int mySword=0, myArch=0, myHorse=0;
    cout << "Amount of swordsmen, archers and horsemen in your army (3 numbers): ";
    cin >> mySword >> myArch >> myHorse;
    int enemyS=0, enemyA=0, enemyH=0;
    cout << endl << "Amount of swordsmen, archers and horsemen in your ENEMY'S army (3 numbers): " << endl;
    cin >> enemyS >> enemyA >> enemyH;

    customArmies.push_back(new Army(0, mySword, myArch, myHorse, 'W', 'L'));
    customArmies.push_back(new Army(1, enemyS, enemyA, enemyH, 'S', 'B'));

    currentState = BattleMap;
}
