
#include "Camera.h"
#include "Entity.h"
#include "Screen.h"

Camera::Camera() {
      
    x               = 0;
    y               = 0;
    boundx0         = 0;
    boundy0         = 0;
    boundx1         = 0;
    boundy1         = 0;
    followingEntity = nullptr;
}


bool Camera::HasBounds() const {
    return boundx0 != boundx1;
}


double Camera::GetMinX() const {
    return boundx0;
}


double Camera::GetMinY() const {
    return boundy0;
}

double Camera::GetMaxX() const {
    return (HasBounds()) ? boundx1 - Screen::Instance().GetWidth() : boundx1;
}

double Camera::GetMaxY() const {
    return HasBounds() ? boundy1 - Screen::Instance().GetWidth() : boundy1;
}

void Camera::Update() {

    if (followingEntity) {

        double midX = (x * 2 + Screen::Instance().GetWidth()) / 2;
        double midY = (y * 2 + Screen::Instance().GetHeight()) / 2;

        if (followingEntity->GetX() < midX ||
            followingEntity->GetX() > midX ||
            followingEntity->GetY() < midY ||
            followingEntity->GetY() > midY) {

            double mX = followingEntity->GetX() - midX;
            double mY = followingEntity->GetY() - midY;

            SetX(x + mX);
            SetY(y + mY);
        }
    }
}

void Camera::SetBounds(double bx0, double by0, double bx1, double by1) {
    boundx0 = bx0;
    boundy0 = by0;
    boundx1 = bx1;
    boundy1 = by1;
}


void Camera::SetX(double x) {

    if (HasBounds()) {

        if (x < GetMinX()) {
            x = GetMinX();
        }

        if (x > GetMaxX()) {
            x = GetMaxX();
        }
    }
    this->x = x;
}

void Camera::SetY(double y) {

    if (HasBounds()) {

        if (y < GetMinY()) {
            y = GetMinY();
        }

        if (y > GetMaxY()) {
            y = GetMaxY();
        }
    }
    this->y = y;
}
