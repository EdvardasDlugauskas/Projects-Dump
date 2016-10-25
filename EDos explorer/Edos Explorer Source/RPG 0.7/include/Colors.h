#ifndef COLORS_H
#define COLORS_H

#include "Level.h"

#include <windows.h>
#include <iostream>
#include <string>
#include <thread>
#include <stdio.h> // printf
#include <stdexcept> // for exceptions in setWindow()

using namespace std;        // remove later

class Colors
{
    public:
                //Colors
        static void ShowConsoleCursor(bool showFlag);
        static void printStringInColor(std::string tiles);
        static void defaultColors();
        static void printInColor(char tile);

                //Sounds
        static void coinSound();
        static void moveSound();
        static void blockedSound();
        static void teleportSound();
        static void newLevelSound();

        static void soundPlay(std::string name);
        static void SetWindow(int Width, int Height);

};


#endif // COLORS_H
