#pragma once
#include <SDL.h>
#include <string>
class Ball {

public:

	//Constructors
	Ball();
	Ball(float X, float Y, float Radius, float VelocityX, float VelocityY, std::string path);
	Ball(const Ball& ball);
	~Ball();

	//Getters
	float getX();
	float getY();
	float getRadius();
	float getVelocityX();
	float getVelocityY();

	//Setters
	void setX(float X);
	void setY(float Y);
	void setRadius(float Radius);
	void setVelocityX(float VelocityX);
	void setVelocityY(float VelocityY);

	//Methods
	void Update();
	void InvertVelX();
	void InvertVelY();
	void render();

private:
	float x;
	float y;
	float radius;
	float velocityX;
	float velocityY;

	class Texture* _texture;
	std::string _path;
};