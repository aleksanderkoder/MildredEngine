#pragma once

class Player
{
public:
    double positionX, positionY, size, viewAngle, speed, posXCentered, posYCentered;
    Player(double positionX, double positionY, double size, double viewAngle, double speed);
    void DrawAngleLine();
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void AdjustAngle(int* xrel, int* yrel);
    void DrawPlayerOnMinimap(); 
    void UpdateCenteredPosition(); 
};

