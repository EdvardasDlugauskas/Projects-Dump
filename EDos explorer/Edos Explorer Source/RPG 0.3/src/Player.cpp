#include "Player.h"

Player::Player()
{
    playerX = 1;
    playerY = 1;
}

void Player::initialize()
{

}

void Player::getPosition(int &x, int &y)    // sets given ints to actual coordinates!
{
    x = playerX;
    y = playerY;
}

void Player::setPosition(int x, int y)
{
    playerX = x;
    playerY = y;
}
