#include "Player.h"

Player::Player()
{
    playerX = 0;
    playerY = 0;
}

void Player::initialize(int level, int health, int attack, int defense, int experience)
{
    PlayerLevel = level;
    PlayerHealth = health;
    PlayerAttack = attack;
    PlayerDefense = defense;
    PlayerExperience = experience;
}

void Player::getPosition(int &x, int &y)
{
    x = playerX;
    y = playerY;
}

void Player::setPosition(int x, int y)
{
    playerX = x;
    playerY = y;
}
