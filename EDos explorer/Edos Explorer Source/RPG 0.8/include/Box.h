#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <windows.h>

using namespace std;


class Box
{
    public:
        Box();
        void setBox(int X, int Y, int Width, int Height);
        void drawBox();
    protected:

    private:
        bool gotoxy(int x, int y);  // just for use in this class

        int x, y, width, height;
};

#endif // BOX_H
