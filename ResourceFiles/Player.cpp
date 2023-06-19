#include "../HeaderFiles/Player.h"
#include "../HeaderFiles/MGDTexture.h"
#include "../HeaderFiles/Constants.h"

//Constructors
Player::Player() {
    this->x = 0;
    this->y = 0;
    this->speed = 0;
    this->_path = "";
    _texture = new MGDTexture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        this->width = _texture->getWidth();
        this->height = _texture->getHeight();
    }
}
Player::Player(float X, float Y, float Speed, std::string path) {
    this->x = X;
    this->y = Y;
    this->speed = Speed;
    this->_path = path;
    _texture = new MGDTexture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        this->width = _texture->getWidth();
        this->height = _texture->getHeight();
    }
}
Player::Player(const Player& player) {
    this->x = player.x;
    this->y = player.y;
    this->speed = player.speed;
    this->_path = player._path;
    _texture = new MGDTexture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        this->width = _texture->getWidth();
        this->height = _texture->getHeight();
    }
}
Player::~Player() {
    _texture->free();
    delete _texture;
}

//Getters
float Player::getX() {
    return this->x;
}
float Player::getY() {
    return this->y;
}
float Player::getWidth() {
    return this->width;
}
float Player::getHeight() {
    return this->height;
}
float Player::getSpeed() {
    return this->speed;
}

//Setters
void Player::setX(float X) {
    this->x = X;
}
void Player::setY(float Y) {
    this->y = Y;
}
void Player::setWidth(float Width) {
    this->width = Width;
}
void Player::setHeight(float Height) {
    this->height = Height;
}
void Player::setSpeed(float Speed) {
    this->speed = Speed;
}

//Methods
void Player::handleEvent(SDL_Event& sdlEvent) {
    // If a key was pressed
    if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.repeat == 0) {
        // Adjust the velocity
        switch (sdlEvent.key.keysym.sym) {
        case SDLK_LEFT:
        case 'a':
            this->speed -= this->speed;

            break;
        case SDLK_RIGHT:
        case 'd':
            this->speed += this->speed;

            break;
        }
    }
    // If a key was released
    else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.repeat == 0) {
        // Adjust the velocity
        switch (sdlEvent.key.keysym.sym) {
        case SDLK_LEFT:
        case 'a':
            this->speed += this->speed;
            break;
        case SDLK_RIGHT:
        case 'd':
            this->speed -= this->speed;
            break;
        }
    }
}

void Player::move(double timeStep) {
    // Move the texture left or right
    this->x += this->speed * timeStep;

    // If the texture went too far to the left or right
    if (this->x < 10) {
        this->setX(10);
    }
    else if (this->x > SCREEN_WIDTH - this->getWidth()-10) {
        this->setX(SCREEN_WIDTH - this->getWidth() - 10);
    }
}

void Player::render() {
    // Show the texture
    _texture->render((int)this->getX(), (int)this->getY());
}