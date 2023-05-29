#pragma once
class Player {

public:

    //Constructors
    Player();
    Player(int X, int Y, int Width, int Height, int Speed);
    Player(const Player& player);

    //Getters
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    int getSpeed();

    //Setters
    void setX(int X);
    void setY(int Y);
    void setWidth(int Width);
    void setHeight(int Height);
    void setSpeed(int Speed);

private:
    int x;
    int y;
    int width;
    int height;
    int speed;
};