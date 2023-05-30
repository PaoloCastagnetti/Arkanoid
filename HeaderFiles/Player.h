#pragma once
class Player {

public:

    //Constructors
    Player();
    Player(float X, float Y, float Width, float Height, float Speed);
    Player(const Player& player);

    //Getters
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    float getSpeed();

    //Setters
    void setX(float X);
    void setY(float Y);
    void setWidth(float Width);
    void setHeight(float Height);
    void setSpeed(float Speed);

private:
    float x;
    float y;
    float width;
    float height;
    float speed;
};