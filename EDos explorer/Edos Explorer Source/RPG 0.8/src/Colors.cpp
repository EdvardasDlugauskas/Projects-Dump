#include "Colors.h"

void Colors::printInColor(char tile)
{
    int colorNumber = 8;    // default

    switch (tile)
        {
        case '#':
            colorNumber = 24;   // blue background gray text
            break;
        case Level::userTileUp:
        case Level::userTileDown:
        case Level::userTileLeft:
        case Level::userTileRight:
            colorNumber = 12;   // red
            break;
        case '.':
            tile = ' ';
            colorNumber = 15;   // whitest
            break;
        case '[':
        case ']':
            colorNumber = 6;    // dark yellow
            break;
        case 'Q':
            colorNumber = 13;   // purple
            break;
        case '$':
            colorNumber = 10;   // green
            break;
        case ' ':
            colorNumber = 8;    // black?
            break;
        case '!':
            colorNumber = 12;   // red
            break;
        case '+':
        case '-':
            colorNumber = 19;
            break;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNumber);
        printf("%c", tile);
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

void Colors::defaultColors ()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);        // 8 is the default colors
}

void Colors::soundPlay(std::string name)    // play entered sound
{
    const char * c = name.c_str();
    PlaySound(TEXT(c), NULL, SND_FILENAME  | SND_NODEFAULT  | SND_APPLICATION);
}

void Colors::coinSound()
{
    PlaySound(TEXT(".\\sounds\\coin.wav"), NULL, SND_FILENAME  | SND_NODEFAULT | SND_ASYNC);
    Sleep(100);
}

void Colors::moveSound()
{
    PlaySound( ".\\sounds\\moving.wav" , NULL, SND_FILENAME | SND_ASYNC);  // SND_ASYNC means it will run in background, SYNC - wait for sound to finish before everything else
    Sleep(100);
}

void Colors::blockedSound()
{
     PlaySound(TEXT(".\\sounds\\blocked.wav"), NULL, SND_FILENAME  | SND_NODEFAULT );
     Sleep(100);
}

void Colors::teleportSound()
{
     PlaySound(TEXT(".\\sounds\\teleport.wav"), NULL, SND_FILENAME  | SND_NODEFAULT | SND_ASYNC);
     Sleep(100);
}

void Colors::newLevelSound()
{
    PlaySound(TEXT(".\\sounds\\newLevel.wav"), NULL, SND_FILENAME  | SND_NODEFAULT | SND_ASYNC);
}


void Colors::SetWindow(int x, int y)
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
