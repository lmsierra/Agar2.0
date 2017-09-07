#include "Player.h"
#include "Math.h"
#include <stdio.h>
#include "PeerENet.h"

Player::Player() : Entity() {
    isMoving  = false;
    dirX      = 0;
    dirY      = 0;
    destX     = 0;
    destY     = 0;
    peer      = nullptr;
}

Player::Player(double x, double y) : Entity(x, y) {
    isMoving  = false;
    dirX      = 0;
    dirY      = 0;
    destX     = 0;
    destY     = 0;
    peer      = nullptr;
}

Player::Player(double x, double y, uint32 w) : Entity(x, y, w) {
    isMoving = false;
    dirX     = 0;
    dirY     = 0;
    destX    = 0;
    destY    = 0;
    peer     = nullptr;
}

void Player::MoveTo(double x, double y) {

    if (GetX() == x && GetY() == y) return;

    isMoving = true;
    destX    = x;
    destY    = y;

    double length = Distance(destX, destY, GetX(), GetY());
    dirX = (destX - GetX()) / length;
    dirY = (destY - GetY()) / length;
}


void Player::Update(double deltaTime) {
    
    if (isMoving)
    {
        speed = Lerp(MIN_SPEED, MAX_SPEED, 1.f - GetWeight() / MAX_WEIGHT_SPEED);

        double nextStepX = dirX * speed * deltaTime;
        double nextStepY = dirY * speed * deltaTime;

        if (Distance(destX, destY, GetX(), GetY()) < Distance(destX, destY, destX + nextStepX, destY + nextStepY))
        {
            SetX(destX);
            SetY(destY);
            isMoving = false;
        }
        else
        {
            SetX(GetX() + nextStepX);
            SetY(GetY() + nextStepY);
        }
    }
}
