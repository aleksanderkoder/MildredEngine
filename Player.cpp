#include "Player.h"
#include "Mildred.h"
#include "Calc.h"
#include <cmath>

//double positionX, positionY, size, viewAngle, speed; 

Player::Player(int _positionX, int _positionY, int _size, int _viewAngle, double _speed)
{
    positionX = _positionX;
    positionY = _positionY;
    size = _size;
    viewAngle = Calc::ToRadians(_viewAngle);
    speed = _speed;
    
}

void Player::MoveForward() {
    positionX = round(positionX + cos(viewAngle) * speed);
    positionY = round(positionY + sin(viewAngle) * speed);
}
void Player::MoveBackward()
{
    positionX = round(positionX + cos(viewAngle + Calc::ToRadians(180)) * speed);
    positionY = round(positionY + sin(viewAngle + Calc::ToRadians(180)) * speed);
}
void Player::MoveLeft()
{
    positionX = round(positionX + cos(viewAngle - Calc::ToRadians(90)) * speed);
    positionY = round(positionY + sin(viewAngle - Calc::ToRadians(90)) * speed);
}
void Player::MoveRight()
{
    positionX = round(positionX + cos(viewAngle + Calc::ToRadians(90)) * speed);
    positionY = round(positionY + sin(viewAngle + Calc::ToRadians(90)) * speed);
}
void Player::DrawAngleLine() {
    Mildred::SetRenderDrawColor(128, 0, 155, 255);

    int x2 = (int)round(positionX + cos(viewAngle) * 40);
    int y2 = (int)round(positionY + sin(viewAngle) * 40);
    SDL_RenderDrawLine(Mildred::GetRenderer(), (int)(positionX + size / 2), (int)(positionY + size / 2),
        x2, y2);
}

void Player::AdjustAngle(int* xrel, int* yrel)
{
    viewAngle += Calc::ToRadians(*xrel / 3);
    //Console.WriteLine(viewAngle);
    //viewAngle += yrel; 
}

void Player::DrawPlayerOnMinimap() {
    Mildred::SetRenderDrawColor(0, 255, 0, 255);
    Mildred::DrawRect((int)size, (int)size, (int)positionX, (int)positionY);
    DrawAngleLine();
}