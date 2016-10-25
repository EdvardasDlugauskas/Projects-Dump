#include "Colors.h"

void Colors::printInColor(char tile)
{
    int colorNumber = 8;    // default

    switch (tile)
        {
        case '#':
            colorNumber = 24;   // blue back grey text
            break;
        case '@':
            colorNumber = 12;
            break;
        case '.':
            tile = ' ';
            colorNumber = 15;   // whitest
            break;
        case '[':
        case ']':
            colorNumber = 8;    // gray
            break;
        case 'Q':
            colorNumber = 13;   // red
            break;
        case '$':
            colorNumber = 10;   // yellow
            break;
        case '!':
            colorNumber = 13;
            break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNumber);
        std::cout << tile;
}

void Colors::printStringInColor(std::string tiles)
{
    char chArray[64];
    int stringSize = tiles.size();
    for (int i = 0; i <= stringSize; i++) chArray[i] = tiles[i];    // convert string to char array

    for (int i = 0; i <= stringSize; i++) printInColor( chArray[i] );
    defaultColors();    // in case we write something after



}

void Colors::ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Colors::defaultColors ()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);        // 8 is the default colors
}
