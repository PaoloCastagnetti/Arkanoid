/**
 * @file Block.cpp
 * @brief Implementation file for the Block class.
 */

#include "../HeaderFiles/Block.h"
#include "../HeaderFiles/MGDTexture.h"
#include "../HeaderFiles/Constants.h"

//Constructors

/**
 * @brief Default constructor for the Block class.
 * Initializes the block's position, dimensions, destroyed state, and texture.
 */
Block::Block() {
	// Initialize block properties
	this->x = 0;
	this->y = 0;
	this->width = BLOCK_WIDTH;
	this->height = BLOCK_HEIGHT;
	this->destroyed = false;
	this->_texture = new Texture();
}

/**
 * @brief Parameterized constructor for the Block class.
 * Initializes the block's position, dimensions, destroyed state, and texture with the given values.
 * Loads the texture from the specified file path.
 * @param X The X position of the block.
 * @param Y The Y position of the block.
 * @param Destroyed The destroyed state of the block.
 * @param path The file path of the texture to load.
 */
Block::Block(int X, int Y, bool Destroyed, std::string path) {
	// Initialize block properties
	this->x = X;
	this->y = Y;
	this->width = BLOCK_WIDTH;
	this->height = BLOCK_HEIGHT;
	this->destroyed = Destroyed;
	this->_texture = new Texture();
	if (!this->_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->width = this->_texture->getWidth();
		this->height = this->_texture->getHeight();
	}
}

/**
 * @brief Copy constructor for the Block class.
 * Creates a new Block object by copying the properties of another Block object.
 * Loads the texture from the specified file path.
 * @param block The Block object to be copied.
 */
Block::Block(const Block& block) {
	// Copy block properties
	this->x = block.x;
	this->y = block.y;
	this->width = BLOCK_WIDTH;
	this->height = BLOCK_HEIGHT;
	this->destroyed = block.destroyed;
	this->_texture = new Texture();
	if (!this->_texture->loadFromFile(block._path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->width = this->_texture->getWidth();
		this->height = this->_texture->getHeight();
	}
}

/**
 * @brief Destructor for the Block class.
 * Frees the texture resources and deletes the texture object.
 */
Block::~Block() {
	_texture->free();
	delete this->_texture;
}

//Getters

/**
 * @brief Getter for the X position of the block.
 * @return The X position of the block.
 */
int Block::getX() {
	return this->x;
}

/**
 * @brief Getter for the Y position of the block.
 * @return The Y position of the block.
 */
int Block::getY() {
	return this->y;
}

/**
 * @brief Getter for the width of the block.
 * @return The width of the block.
 */
int Block::getWidth() {
	return this->width;
}

/**
 * @brief Getter for the height of the block.
 * @return The height of the block.
 */
int Block::getHeight() {
	return this->height;
}

/**
 * @brief Getter for the destroyed state of the block.
 * @return True if the block is destroyed, false otherwise.
 */
bool Block::getDestroyed() {
	return this->destroyed;
}

//Setters

/**
 * @brief Setter for the X position of the block.
 * @param X The new X position of the block.
 */
void Block::setX(int X) {
	this->x = X;
}

/**
 * @brief Setter for the Y position of the block.
 * @param Y The new Y position of the block.
 */
void Block::setY(int Y) {
	this->y = Y;
}

/**
 * @brief Setter for the width of the block.
 * @param Width The new width of the block.
 */
void Block::setWidth(int Width) {
	this->width = Width;
}

/**
 * @brief Setter for the height of the block.
 * @param Height The new height of the block.
 */
void Block::setHeight(int Height) {
	this->height = Height;
}

/**
 * @brief Setter for the destroyed state of the block.
 * @param Destroyed The new destroyed state of the block.
 */
void Block::setDestroyed(bool Destroyed) {
	this->destroyed = Destroyed;
}

//Methods

/**
 * @brief Renders the block's texture on the screen.
 */
void Block::render() {
	// Show the texture
	_texture->render(this->getX(), this->getY());
}

/**
 * @brief Sets a new texture for the block.
 * Loads the texture from the specified file path and updates the block's dimensions.
 * @param _path The new file path of the texture to load.
 */
void Block::setTexture(std::string _path) {
	this->_texture->free();
	this->_texture = new Texture();
	if (!this->_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->width = this->_texture->getWidth();
		this->height = this->_texture->getHeight();
	}
}