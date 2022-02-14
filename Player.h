#pragma once

class Player
{
public:
    double positionX, positionY, size, viewAngle, speed;
    Player(double _positionX, double _positionY, double _size, double _viewAngle, double _speed);
    void DrawAngleLine();
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void AdjustAngle(int* xrel, int* yrel);
    void DrawPlayerOnMinimap(); 

};

