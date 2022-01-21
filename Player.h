#pragma once

class Player
{
public:
    double positionX, positionY, size, viewAngle, speed;
    Player(int _positionX, int _positionY, int _size, int _viewAngle, double _speed);
    void DrawAngleLine();
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void AdjustAngle(int* xrel, int* yrel);
    void DrawPlayerOnMinimap(); 

};

