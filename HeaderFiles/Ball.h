#pragma once
class Ball {

public:

	//Constructors
	Ball();
	Ball(float X, float Y, float Radius, float VelocityX, float VelocityY);
	Ball(const Ball& ball);

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

private:
	float x;
	float y;
	float radius;
	float velocityX;
	float velocityY;
};