#include "Colors.h"

std::mt19937 Colors::mt;

void Colors::printInColor(char tile)
{
    int colorNumber = 8;    // default

    switch (tile)
        {
        case '#':
            colorNumber = 24;   // blue background gray text
            break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNumber);
        printf("%c", tile);
        defaultColors();    // in case we write something after
}

void Colors::printUnitColor(Unit* printedUnit)
{
    char unit = printedUnit->getUnitChar();
    int armyNum = printedUnit->getArmyNumber();
    int colorNumber = 8;
    int backgroundColor = 0;
    if (!printedUnit->isStillAlive()) goto print;



    switch (armyNum)
        {
        case 0:
            colorNumber = 12;   // RED
            break;
        case 1:
            colorNumber = 13;
            break;
        case 2:
            colorNumber = 14;
            break;
        case 3:
            colorNumber = 11;
            break;
        case -1:
            colorNumber = 8;
            break;
        }

    if (printedUnit->getKing() == printedUnit)  // if King
    {
        backgroundColor = colorNumber;
        colorNumber = 0;
    }
        //! Printing
        print:
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backgroundColor*16 + colorNumber);
    printf("%c", unit);
    defaultColors();    // in case we write something after
}

void Colors::printStringInColor(std::string tiles)
{
    char chArray[64];
    int stringSize = tiles.size();
    for (int i = 0; i <= stringSize; i++) chArray[i] = tiles[i];    // convert string to char array

    for (int i = 0; i <= stringSize; i++) printInColor( chArray[i] );


}

void Colors::ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Colors::setPrintColor(int armyNumber)
{
    switch (armyNumber)
    {
        case 0:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);   //  red?
            break;
        case 1:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
            break;
        case 2:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            break;
        case 3:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            break;
        case 4:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            break;
        case 5:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
            break;
        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            break;
    }


}

void Colors::defaultColors ()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);        // 8 is the default colors
}

void Colors::gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;

    std::cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

void Colors::setWindowSize(int x, int y)
{
    COORD consoleSize;
    consoleSize.X = x;
    consoleSize.Y = y;

        try
        {
            HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    if (h == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Unable to get stdout handle.");

    // If either dimension is greater than the largest console window we can have,
    // there is no point in attempting the change.
    {
        COORD largestSize = GetLargestConsoleWindowSize(h);
        if (x > largestSize.X)
            throw std::invalid_argument("The x dimension is too large.");
        if (y > largestSize.Y)
            throw std::invalid_argument("The y dimension is too large.");
    }


    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    if (!GetConsoleScreenBufferInfo(h, &bufferInfo))
        throw std::runtime_error("Unable to retrieve screen buffer info.");

    SMALL_RECT& winInfo = bufferInfo.srWindow;
    COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1};

    if (windowSize.X > x || windowSize.Y > y)
    {
        // window size needs to be adjusted before the buffer size can be reduced.
        SMALL_RECT info =
        {
            0,
            0,
            x < windowSize.X ? x-1 : windowSize.X-1,
            y < windowSize.Y ? y-1 : windowSize.Y-1
        };

        if (!SetConsoleWindowInfo(h, TRUE, &info))
            throw std::runtime_error("Unable to resize window before resizing buffer.");
    }

    COORD size = { x, y };
    if (!SetConsoleScreenBufferSize(h, size))
        throw std::runtime_error("Unable to resize screen buffer.");


    SMALL_RECT info = { 0, 0, x - 1, y - 1 };
    if (!SetConsoleWindowInfo(h, TRUE, &info))
        throw std::runtime_error("Unable to resize window after resizing buffer.");

        }
        catch (std::logic_error& ex)
        {
            std::cerr << ex.what() << '\n';
        }

        catch (std::exception& ex)
        {
            std::cerr << ex.what() << "\nSystem error: ";
    }
}




//! RANDOM
void Colors::initRNG()
{
//    SYSTEMTIME time;   // "SYSTEMTIME" object called "time" (can be called anything)
//    GetSystemTime(&time);   // get current time ( & - address of the object...)
//    mt.seed(time.wMilliseconds + time.wSecond*1000);
    mt.seed(15102);
}

int Colors::getRNG(short low, short high)
{
    std::uniform_int_distribution<int> dist(low, high);
    return dist(mt);
}
