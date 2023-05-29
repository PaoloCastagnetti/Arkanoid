#pragma once
class Block {

public:

    //Constructors
    Block();
    Block(int X, int Y, bool Destroyed);
    Block(const Block& block);

    //Getters
    int getX();
    int getY();
    bool getDestroyed();

    //Setters
    void setX(int X);
    void setY(int Y);
    void setDestroyed(bool Destroyed);

private:
    int x;
    int y;
    bool destroyed;
};