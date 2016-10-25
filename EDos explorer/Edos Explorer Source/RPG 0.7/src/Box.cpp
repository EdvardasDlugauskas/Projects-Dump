#include "Box.h"

Box::Box()
{
}
bool Box::gotoxy(int x, int y)
{
    COORD c = {x,y};
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void Box::drawBox()
{
    gotoxy(x, y); cout << char(201);
    for (int i = 1; i < width; i++) cout << char (205);
    cout << char(187);
    gotoxy(x, height + y); cout << char (200);
    for (int i = 1; i < width; i++) cout << char(205);
    cout << char(188);
    for(int i = y + 1; i < height + y; i++)
    {
        gotoxy(x,i); cout << char (186);
        gotoxy(x + width, i); cout << char(186);
    }
}

void Box::setBox(int X, int Y, int Width, int Height)
{
    x=X;
    y=Y;
    width=Width;
    height=Height;
}
