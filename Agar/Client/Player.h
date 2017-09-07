#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

class Player : public Entity {

public:

    Player();
    Player(double x, double y);
    Player(double x, double y, uint32 w);

    virtual void MoveTo(double x, double y);
    virtual void Update(double deltaTime);

    void SetSpeed(float _s) { speed = _s;}
    float GetSpeed() const {return speed;}

private:
    bool   isMoving;
    double destX, destY;
    double dirX,  dirY;
    float  speed;
};

#endif /* __PLAYER_H__ */