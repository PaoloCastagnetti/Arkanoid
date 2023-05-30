#include "../HeaderFiles/Player.h"

//Constructors
Player::Player() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    this->speed = 0;
}
Player::Player(float X, float Y, float Width, float Height, float Speed) {
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
float Player::getX() {
    return this->x;
}
float Player::getY() {
    return this->y;
}
float Player::getWidth() {
    return this->width;
}
float Player::getHeight() {
    return this->height;
}
float Player::getSpeed() {
    return this->speed;
}

//Setters
void Player::setX(float X) {
    this->x = X;
}
void Player::setY(float Y) {
    this->y = Y;
}
void Player::setWidth(float Width) {
    this->width = Width;
}
void Player::setHeight(float Height) {
    this->height = Height;
}
void Player::setSpeed(float Speed) {
    this->speed = Speed;
}