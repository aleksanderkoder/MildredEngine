#pragma once
#include "Mildred.h"

class Player
{
public: 
    double positionX, positionY, size, viewAngle, speed;
    Player(int _positionX, int _positionY, int _size, int _viewAngle, double _speed)
    {
        positionX = _positionX;
        positionY = _positionY;
        size = _size;
        viewAngle = Mildred::Calc::ToRadians(_viewAngle);
        speed = _speed;

    }
};

