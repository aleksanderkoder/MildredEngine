#include "Player.h"
#include "Mildred.h"
#include "Calc.h"
#include <cmath>


Player::Player(double positionX, double positionY, double size, double viewAngle, double speed)
{
    Player::positionX = positionX;
    Player::positionY = positionY;
    Player::size = size;
    Player::viewAngle = Calc::ToRadians(viewAngle);
    Player::speed = speed;
    
}

void Player::MoveForward() {
    Player::positionX = round(Player::positionX + cos(Player::viewAngle) * Player::speed);
    Player::positionY = round(Player::positionY + sin(Player::viewAngle) * Player::speed);
}
void Player::MoveBackward()
{
    Player::positionX = round(Player::positionX + cos(Player::viewAngle + Calc::ToRadians(180)) * Player::speed);
    Player::positionY = round(Player::positionY + sin(Player::viewAngle + Calc::ToRadians(180)) * Player::speed);
}
void Player::MoveLeft()
{
    Player::positionX = round(Player::positionX + cos(Player::viewAngle - Calc::ToRadians(90)) * Player::speed);
    Player::positionY = round(Player::positionY + sin(Player::viewAngle - Calc::ToRadians(90)) * Player::speed);
}
void Player::MoveRight()
{
    Player::positionX = round(Player::positionX + cos(Player::viewAngle + Calc::ToRadians(90)) * Player::speed);
    Player::positionY = round(Player::positionY + sin(Player::viewAngle + Calc::ToRadians(90)) * Player::speed);
}
void Player::DrawAngleLine() {
    Mildred::SetRenderDrawColor(128, 0, 155, 255);

    int x2 = round(Player::positionX + Player::size / 2 + cos(Player::viewAngle) * 150);
    int y2 = round(Player::positionY + Player::size / 2 + sin(Player::viewAngle) * 150);
    SDL_RenderDrawLine(Mildred::GetRenderer(), Player::positionX + size / 2, Player::positionY + Player::size / 2,
        x2, y2);
}

void Player::AdjustAngle(int* xrel, int* yrel)
{
    Player::viewAngle += Calc::ToRadians(*xrel / 3);
    //Console.WriteLine(viewAngle);
    //viewAngle += yrel; 
}

void Player::DrawPlayerOnMinimap() {
    Mildred::SetRenderDrawColor(0, 255, 0, 255);
    Mildred::DrawRect(Player::size, Player::size, Player::positionX, Player::positionY);
    DrawAngleLine();
}