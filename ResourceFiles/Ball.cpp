#include "../HeaderFiles/Ball.h"
#include "../HeaderFiles/MGDTexture.h"
#include "../HeaderFiles/Constants.h"

//Constructors
Ball::Ball(){
	this->x = 0;
	this->y = 0;
	this->radius = 0;
	this->velocityX = 0;
	this->velocityY = 0;
	this->_path = "";
	_texture = new MGDTexture();
	if (!_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->radius = _texture->getWidth()/2;
	}
}
Ball::Ball(float X, float Y, float Radius, float VelocityX, float VelocityY, std::string path){
	this->x = X;
	this->y = Y;
	this->radius = Radius;
	this->velocityX = VelocityX;
	this->velocityY = VelocityY;
	this->_path = path;
	_texture = new MGDTexture();
	if (!_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->radius = _texture->getWidth()/2;
	}
}
Ball::Ball(const Ball& ball){
	this->x = ball.x;
	this->y = ball.y;
	this->radius = ball.radius;
	this->velocityX = ball.velocityX;
	this->velocityY = ball.velocityY;
	this->_path = ball._path;
	_texture = new MGDTexture();
	if (!_texture->loadFromFile(_path)) {
		printf("Failed to load the texture!\n");
	}
	else {
		this->radius = _texture->getWidth()/2;
	}
}
Ball::~Ball() {
	_texture->free();
	delete _texture;
}

//Getters
float Ball::getX(){
	return this->x;
}
float Ball::getY(){
	return this->y;
}
float Ball::getRadius(){
	return this->radius;
}
float Ball::getVelocityX(){
	return this->velocityX;
}
float Ball::getVelocityY(){
	return this->velocityY;
}

//Setters
void Ball::setX(float X){
	this->x = X;
}
void Ball::setY(float Y){
	this->y = Y;
}
void Ball::setRadius(float Radius){
	this->radius = Radius;
}
void Ball::setVelocityX(float VelocityX){
	this->velocityX = VelocityX;
}
void Ball::setVelocityY(float VelocityY){
	this->velocityY = VelocityY;
}
//Methods
void Ball::Update() {
	this->x += this->velocityX;
	this->y += this->velocityY;
}

void Ball::InvertVelX() {
	this->velocityX = -this->velocityX;
}

void Ball::InvertVelY() {
	this->velocityY = -this->velocityY;
}

void Ball::render() {
	// Show the texture
	_texture->render((int)this->getX(), (int)this->getY());
}