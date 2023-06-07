#pragma once

#include <SDL.h>
#include <string>

// The texture that will move around on the screen
class MovableTexture {
public:
    // Initializes the variables
    MovableTexture();

    // Initializes the variables and tries to load a texture from the path
    MovableTexture(std::string path);

    // Deinitializes the variables
    ~MovableTexture();

    // Takes key presses and adjusts the texture's velocity
    void handleEvent(SDL_Event& sdlEvent);

    // Moves the texture
    void move(double timeStep);

    // Shows the texture on the screen
    void render();

    // Sets the position of this texture (0,0 is the top left)
    void setPosX(double posX);
    void setPosY(double posY);

    // Gets the position of this texture (0,0 is the top left)
    const double getPosX();
    const double getPosY();

private:
    double _posX, _posY;
    double _velX, _velY;

    // The dimensions of the texture
    int _textureWidth = 20;
    int _textureHeight = 20;

    // Maximum axis velocity of the texture
    int _velocity = 200;

    // Scene textures
    class Texture* _texture;

    std::string _path;
};
