#pragma once
#include <SDL.h>
#include <string>
class Player {

public:

    //Constructors
    Player();
    Player(float X, float Y, float Speed, std::string path);
    Player(const Player& player);
    ~Player();

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

    //Methods
    void handleEvent(SDL_Event& sdlEvent);
    void render();
    void setTexture(std::string _path);

private:
    float x;
    float y;
    float _velX;
    float width;
    float height;
    float speed;

    class Texture* _texture;
    std::string _path;
};