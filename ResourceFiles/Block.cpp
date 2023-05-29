#include "../HeaderFiles/Block.h"

//Constructors
Block::Block() {
	this->x = 0;
	this->y = 0;
	this->destroyed = false;
}
Block::Block(int X, int Y, bool Destroyed) {
	this->x = X;
	this->y = Y;
	this->destroyed = Destroyed;
}
Block::Block(const Block& block) {
	this->x = block.x;
	this->y = block.y;
	this->destroyed = block.destroyed;
}

//Getters
int Block::getX() {
	return this->x;
}
int Block::getY() {
	return this->y;
}
bool Block::getDestroyed() {
	return this->destroyed;
}

//Setters
void Block::setX(int X) {
	this->x = X;
}
void Block::setY(int Y) {
	this->y = Y;
}
void Block::setDestroyed(bool Destroyed) {
	this->destroyed = Destroyed;
}