#include "Player.h"
#include "Mildred.h"
#include "Calc.h"
#include <cmath>


Player::Player(double positionX, double positionY, double size, double viewAngle, double speed)
{
    this->positionX = positionX;
    this->positionY = positionY;
    this->size = size;
    this->viewAngle = Calc::ToRadians(viewAngle);
    this->speed = speed;
    this->posXCentered = positionX + size / 2;
    this->posYCentered = positionY + size / 2;
    
}

void Player::MoveForward() {
    this->positionX = this->positionX + cos(this->viewAngle) * this->speed;
    this->positionY = this->positionY + sin(this->viewAngle) * this->speed;
    this->UpdateCenteredPosition();
}
void Player::MoveBackward()
{
    this->positionX = this->positionX + cos(this->viewAngle + Calc::ToRadians(180)) * this->speed;
    this->positionY = this->positionY + sin(this->viewAngle + Calc::ToRadians(180)) * this->speed;
    this->UpdateCenteredPosition();
}
void Player::MoveLeft()
{
    this->positionX = this->positionX + cos(this->viewAngle - Calc::ToRadians(90)) * this->speed;
    this->positionY = this->positionY + sin(this->viewAngle - Calc::ToRadians(90)) * this->speed;
    this->UpdateCenteredPosition();
}
void Player::MoveRight()
{
    this->positionX = this->positionX + cos(this->viewAngle + Calc::ToRadians(90)) * this->speed;
    this->positionY = this->positionY + sin(this->viewAngle + Calc::ToRadians(90)) * this->speed;
    this->UpdateCenteredPosition();
}
void Player::DrawAngleLine() {
    Mildred::SetRenderDrawColor(128, 0, 155, 255);

    int x2 = this->positionX + this->size / 2 + cos(this->viewAngle) * 150;
    int y2 = this->positionY + this->size / 2 + sin(this->viewAngle) * 150;
    SDL_RenderDrawLine(Mildred::GetRenderer(), this->posXCentered, this->posYCentered,
        x2, y2);
}

void Player::AdjustAngle(int* xrel, int* yrel)
{
    Player::viewAngle += Calc::ToRadians(*xrel / 3);
    //cout << "Viewangle: " << Player::viewAngle << endl;
    //cout << "Normalized angle in radians: " << Calc::NormalizeAngleRad(Player::viewAngle) << endl;
    //viewAngle += yrel; 
}

void Player::DrawPlayerOnMinimap() {
    Mildred::SetRenderDrawColor(0, 255, 0, 255);
    Mildred::DrawRect(this->size, this->size, this->positionX, this->positionY);
    DrawAngleLine();
}

void Player::UpdateCenteredPosition() {
    this->posXCentered = positionX + size / 2;
    this->posYCentered = positionY + size / 2;
}