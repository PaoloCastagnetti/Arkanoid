#pragma once
#include <SDL.h>
#include <string>
#include "../HeaderFiles/MGDTexture.h"
class Block {

public:

    //Constructors
    Block();
    Block(int X, int Y, bool Destroyed, std::string path);
    Block(const Block& block);
    ~Block();

    //Getters
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool getDestroyed();

    //Setters
    void setX(int X);
    void setY(int Y);
    void setWidth(int Width);
    void setHeight(int Height);
    void setDestroyed(bool Destroyed);

    //Methods
    void render();
    void setTexture(std::string _path);

private:
    int x;
    int y;
    int width;
    int height;
    bool destroyed;

    class Texture* _texture;
    std::string _path;
};