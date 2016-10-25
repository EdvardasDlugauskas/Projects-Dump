#ifndef COLORS_H
#define COLORS_H

#include <windows.h>
#include <iostream>
#include <string>


class Colors
{
    public:
        static void ShowConsoleCursor(bool showFlag);
        static void printStringInColor(std::string tiles);
        static void defaultColors();

    private:
        static void printInColor(char tile);

};


#endif // COLORS_H
