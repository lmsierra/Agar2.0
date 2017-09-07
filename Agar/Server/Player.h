#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "ServerENet.h"

#define MAX_SPEED 250.f
#define MIN_SPEED MAX_SPEED*0.1f // minimum speed.
#define MAX_WEIGHT_SPEED 80.f // Max weight needed to use minimum speed

class Player : public Entity {

public:

    Player();
    Player(double x, double y);
    Player(double x, double y, uint32 w);

    virtual void MoveTo(double x, double y);
    virtual void Update(double deltaTime);

    void             SetPeer(ENet::CPeerENet* p) { peer = p;     }
    void             SetSpeed(float s)           { speed = s;    }
    float            GetSpeed() const            { return speed; }
    ENet::CPeerENet* GetPeer()  const            { return peer;  }

private:
    bool             isMoving;
    double           destX, destY;
    double           dirX,  dirY;
    float            speed;
    ENet::CPeerENet* peer;
};

#endif /* __PLAYER_H__ */