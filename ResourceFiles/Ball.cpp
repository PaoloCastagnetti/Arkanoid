/**
 * @file Ball.cpp
 * @brief Implementation file for the Ball class.
 */

#include "../HeaderFiles/Ball.h"
#include "../HeaderFiles/MGDTexture.h"
#include "../HeaderFiles/Constants.h"

//Constructors

/**
 * @brief Default constructor for the Ball class.
 * Initializes the ball's position, radius, velocity, and texture.
 * Loads the texture from the specified file path.
 */
Ball::Ball(){
	// Initialize ball properties
	this->x = 0;
	this->y = 0;
	this->radius = 0;
	this->velocityX = 0;
	this->velocityY = 0;
	this->_path = "";

	// Create and load texture
	_texture = new Texture();
	if (!_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->radius = _texture->getWidth()/2;
	}
}

/**
 * @brief Parameterized constructor for the Ball class.
 * Initializes the ball's position, radius, velocity, and texture with the given values.
 * Loads the texture from the specified file path.
 * @param X The initial X position of the ball.
 * @param Y The initial Y position of the ball.
 * @param Radius The radius of the ball.
 * @param VelocityX The velocity along the X axis of the ball.
 * @param VelocityY The velocity along the Y axis of the ball.
 * @param path The file path of the texture to load.
 */
Ball::Ball(float X, float Y, float Radius, float VelocityX, float VelocityY, std::string path){
	// Initialize ball properties
	this->x = X;
	this->y = Y;
	this->radius = Radius;
	this->velocityX = VelocityX;
	this->velocityY = VelocityY;
	this->_path = path;

	// Create and load texture
	_texture = new Texture();
	if (!_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->radius = _texture->getWidth()/2;
	}
}

/**
 * @brief Copy constructor for the Ball class.
 * Creates a new Ball object by copying the properties of another Ball object.
 * Loads the texture from the specified file path.
 * @param ball The Ball object to be copied.
 */
Ball::Ball(const Ball& ball){
	// Copy ball properties
	this->x = ball.x;
	this->y = ball.y;
	this->radius = ball.radius;
	this->velocityX = ball.velocityX;
	this->velocityY = ball.velocityY;
	this->_path = ball._path;

	// Create and load texture
	_texture = new Texture();
	if (!_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->radius = _texture->getWidth()/2;
	}
}

/**
 * @brief Destructor for the Ball class.
 * Frees the texture resources and deletes the texture object.
 */
Ball::~Ball() {
	_texture->free();
	delete _texture;
}

//Getters

/**
 * @brief Getter for the X position of the ball.
 * @return The X position of the ball.
 */
float Ball::getX(){
	return this->x;
}

/**
 * @brief Getter for the Y position of the ball.
 * @return The Y position of the ball.
 */
float Ball::getY(){
	return this->y;
}

/**
 * @brief Getter for the radius of the ball.
 * @return The radius of the ball.
 */
float Ball::getRadius(){
	return this->radius;
}

/**
 * @brief Getter for the velocity along the X axis of the ball.
 * @return The velocity along the X axis of the ball.
 */
float Ball::getVelocityX(){
	return this->velocityX;
}

/**
 * @brief Getter for the velocity along the Y axis of the ball.
 * @return The velocity along the Y axis of the ball.
 */
float Ball::getVelocityY(){
	return this->velocityY;
}

//Setters

/**
 * @brief Setter for the X position of the ball.
 * @param X The new X position of the ball.
 */
void Ball::setX(float X){
	this->x = X;
}

/**
 * @brief Setter for the Y position of the ball.
 * @param Y The new Y position of the ball.
 */
void Ball::setY(float Y){
	this->y = Y;
}

/**
 * @brief Setter for the radius of the ball.
 * @param Radius The new radius of the ball.
 */
void Ball::setRadius(float Radius){
	this->radius = Radius;
}

/**
 * @brief Setter for the velocity along the X axis of the ball.
 * @param VelocityX The new velocity along the X axis of the ball.
 */
void Ball::setVelocityX(float VelocityX){
	this->velocityX = VelocityX;
}
/**
 * @brief Setter for the velocity along the Y axis of the ball.
 * @param VelocityY The new velocity along the Y axis of the ball.
 */
void Ball::setVelocityY(float VelocityY){
	this->velocityY = VelocityY;
}

//Methods

/**
 * @brief Updates the ball's position based on its velocity.
 * This method should be called in the game loop to update the ball's position in each frame.
 */
void Ball::Update() {
	this->x += this->velocityX;
	this->y += this->velocityY;
}

/**
 * @brief Inverts the velocity along the X axis of the ball.
 * This method is used to change the direction of the ball's movement along the X axis.
 */
void Ball::InvertVelX() {
	this->velocityX = -this->velocityX;
}

/**
 * @brief Inverts the velocity along the Y axis of the ball.
 * This method is used to change the direction of the ball's movement along the Y axis.
 */
void Ball::InvertVelY() {
	this->velocityY = -this->velocityY;
}

/**
 * @brief Renders the ball's texture on the screen.
 */
void Ball::render() {
	// Show the texture
	_texture->render((int)this->getX(), (int)this->getY());
}