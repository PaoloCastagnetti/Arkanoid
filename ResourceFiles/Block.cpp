#include "../HeaderFiles/Block.h"
#include "../HeaderFiles/MGDTexture.h"
#include "../HeaderFiles/Constants.h"

//Constructors
Block::Block() {
	this->x = 0;
	this->y = 0;
	this->width = BLOCK_WIDTH;
	this->height = BLOCK_HEIGHT;
	this->destroyed = false;
	this->_texture = new MGDTexture();
}
Block::Block(int X, int Y, bool Destroyed, std::string path) {
	this->x = X;
	this->y = Y;
	this->width = BLOCK_WIDTH;
	this->height = BLOCK_HEIGHT;
	this->destroyed = Destroyed;
	this->_texture = new MGDTexture();
	if (!this->_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->width = this->_texture->getWidth();
		this->height = this->_texture->getHeight();
	}
}
Block::Block(const Block& block) {
	this->x = block.x;
	this->y = block.y;
	this->width = BLOCK_WIDTH;
	this->height = BLOCK_HEIGHT;
	this->destroyed = block.destroyed;
	this->_texture = new MGDTexture();
	if (!this->_texture->loadFromFile(block._path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->width = this->_texture->getWidth();
		this->height = this->_texture->getHeight();
	}
}
/*
Block::~Block() {
	_texture->free();
	delete this->_texture;
}*/

//Getters
int Block::getX() {
	return this->x;
}
int Block::getY() {
	return this->y;
}
int Block::getWidth() {
	return this->width;
}
int Block::getHeight() {
	return this->height;
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
void Block::setWidth(int Width) {
	this->width = Width;
}
void Block::setHeight(int Height) {
	this->height = Height;
}
void Block::setDestroyed(bool Destroyed) {
	this->destroyed = Destroyed;
}

//Methods
void Block::render() {
	// Show the texture
	_texture->render(this->getX(), this->getY());
}
void Block::setTexture(std::string _path) {
	this->_texture->free();
	this->_texture = new MGDTexture();
	if (!this->_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->width = this->_texture->getWidth();
		this->height = this->_texture->getHeight();
	}
}