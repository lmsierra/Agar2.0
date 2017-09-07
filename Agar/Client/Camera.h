#ifndef __CAMERA_H__
#define __CAMERA_H__

class Entity;

class Camera {

public:
    Camera();
    virtual void   SetPosition(double x, double y) { SetX(x); SetY(y); }
    virtual void   SetX(double x);
    virtual void   SetY(double y);
    virtual double GetX() const { return x; }
    virtual double GetY() const { return y; }
    virtual void   SetBounds(double bx0, double by0, double bx1, double by1);
    virtual bool   HasBounds() const;
    virtual double GetMinX() const;
    virtual double GetMinY() const;
    virtual double GetMaxX() const;
    virtual double GetMaxY() const;
    virtual void   FollowEntity(Entity* entity) { followingEntity = entity; }
    virtual void   Update();

private:
    double x, y;
    double boundx0, boundy0, boundx1, boundy1;
    Entity* followingEntity;
};

#endif /* __CAMERA_H__ */