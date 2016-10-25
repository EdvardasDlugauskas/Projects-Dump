#ifndef COLORS_H
#define COLORS_H

#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h> // printf
#include <stdexcept> // for exceptions in setWindow()
#include <random>
#include "Unit.h"

class Colors
{
    public:
                //!Colors
        static void printStringInColor(std::string tiles);
        static void defaultColors();
        static void printInColor(char tile);
        static void printUnitColor(Unit* printedUnit);

                //!Random
        static void initRNG();
        static int getRNG(short low, short high);

                //!Misc
        static void gotoxy(int x, int y);  // move cursor for printing
        static void ShowConsoleCursor(bool showFlag);
        static void setWindowSize(int x, int y);

        static void setPrintColor(int armyNumber);

        static std::mt19937 mt;
};

#endif // COLORS_H
