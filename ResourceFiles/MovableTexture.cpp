#include "../HeaderFiles/MovableTexture.h"
#include "../HeaderFiles/Texture.h"
#include "../HeaderFiles/Globals.h"
#include "../HeaderFiles/Constants.h"

MovableTexture::MovableTexture()
    : _posX(0)
    , _posY(0)
    , _velX(0)
    , _velY(0)
    , _path("Assets/MissingTexture.bmp") {
    _texture = new Texture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
    }
}

MovableTexture::MovableTexture(std::string path)
    : _posX(0)
    , _posY(0)
    , _velX(0)
    , _velY(0)
    , _path(path) {
    _texture = new Texture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        _textureWidth = _texture->getWidth();
        _textureHeight = _texture->getHeight();
    }
}

MovableTexture::~MovableTexture() {
    // Free loaded images
    _texture->free();
    delete _texture;
}

void MovableTexture::handleEvent(SDL_Event& sdlEvent) {
    // If a key was pressed
    if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0) {
        // Adjust the velocity
        switch (sdlEvent.key.keysym.sym) {
        case SDLK_UP:
        case 'w':
            _velY -= _velocity;
            break;
        case SDLK_DOWN:
        case 's':
            _velY += _velocity;
            break;
        case SDLK_LEFT:
        case 'a':
            _velX -= _velocity;

            break;
        case SDLK_RIGHT:
        case 'd':
            _velX += _velocity;

            break;
        }
    }
    // If a key was released
    else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0) {
        // Adjust the velocity

        switch (sdlEvent.key.keysym.sym) {
        case SDLK_UP:
        case 'w':
            _velY += _velocity;
            break;
        case SDLK_DOWN:
        case 's':
            _velY -= _velocity;
            break;
        case SDLK_LEFT:
        case 'a':
            _velX += _velocity;
            break;
        case SDLK_RIGHT:
        case 'd':
            _velX -= _velocity;
            break;
        }
    }
}

void MovableTexture::move(double timeStep) {
    // Move the texture left or right
    _posX += _velX * timeStep;

    // If the texture went too far to the left or right
    if (_posX < 0) {
        //_posX = 0;
    }
    else if (_posX > SCREEN_WIDTH - _textureWidth) {
        _posX = SCREEN_WIDTH - _textureWidth;
    }

    // Move the texture up or down
    _posY += _velY * timeStep;

    // If the texture went too far up or down
    if (_posY < 0) {
        //_posY = 0;
    }
    else if (_posY > SCREEN_HEIGHT - _textureHeight) {
        _posY = SCREEN_HEIGHT - _textureHeight;
    }
}

void MovableTexture::render() {
    // Show the texture
    _texture->render((int)_posX, (int)_posY);
}

// Sets the position of this texture (0,0 is the top left)
void MovableTexture::setPosX(double posX) {
    _posX = posX;
}
void MovableTexture::setPosY(double posY) {
    _posY = posY;
}

// Gets the position of this texture (0,0 is the top left)
const double MovableTexture::getPosX() {
    return _posX;
}
const double MovableTexture::getPosY() {
    return _posY;
}
