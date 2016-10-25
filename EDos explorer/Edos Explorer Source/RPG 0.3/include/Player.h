#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        Player();

        void setPosition(int x, int y);

        void getPosition(int &x, int &y);

        void initialize();           //Default player properties

    private:
        int playerX,playerY;

};

#endif // PLAYER_H
