#include "../HeaderFiles/Player.h"

//Constructors
Player::Player() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->speed = 0;
}
Player::Player(int X, int Y, int Width, int Height, int Speed) {
    this->x = X;
    this->y = Y;
    this->width = Width;
    this->height = Height;
    this->speed = Speed;
}
Player::Player(const Player& player) {
    this->x = player.x;
    this->y = player.y;
    this->width = player.width;
    this->height = player.height;
    this->speed = player.speed;
}

//Getters
int Player::getX() {
    return this->x;
}
int Player::getY() {
    return this->y;
}
int Player::getWidth() {
    return this->width;
}
int Player::getHeight() {
    return this->height;
}
int Player::getSpeed() {
    return this->speed;
}

//Setters
void Player::setX(int X) {
    this->x = X;
}
void Player::setY(int Y) {
    this->y = Y;
}
void Player::setWidth(int Width) {
    this->width = Width;
}
void Player::setHeight(int Height) {
    this->height = Height;
}
void Player::setSpeed(int Speed) {
    this->speed = Speed;
}