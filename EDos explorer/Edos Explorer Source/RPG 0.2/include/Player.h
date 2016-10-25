#ifndef PLAYER_H
#define PLAYER_H


class Player
{
    public:
        Player();

        void setPosition(int x, int y);

        void getPosition(int &x, int &y);

        void initialize(int level, int health, int attack, int defence, int experience);           //Default player properties

    private:
        int playerX,playerY;

        int PlayerLevel,PlayerHealth,PlayerAttack,PlayerDefense,PlayerExperience; //other player variables;

};

#endif // PLAYER_H
