/**
 * @file Player.cpp
 * @brief Implementation file for the Player class.
 */

#include "../HeaderFiles/Player.h"
#include "../HeaderFiles/MGDTexture.h"
#include "../HeaderFiles/Constants.h"

//Constructors

/**
 * @brief Default constructor for the Player class.
 * Initializes the player's position, speed, and texture.
 * Loads the texture from the specified file path.
 */
Player::Player() {
    // Initialize player properties
    this->x = 0;
    this->y = 0;
    this->speed = 0;
    this->_path = "";

    // Create and load texture
    _texture = new Texture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        this->width = _texture->getWidth();
        this->height = _texture->getHeight();
    }
}

/**
 * @brief Parameterized constructor for the Player class.
 * Initializes the player's position, speed, and texture with the given values.
 * Loads the texture from the specified file path.
 * @param X The initial X position of the player.
 * @param Y The initial Y position of the player.
 * @param Speed The speed of the player.
 * @param path The file path of the texture to load.
 */
Player::Player(float X, float Y, float Speed, std::string path) {
    // Initialize player properties
    this->x = X;
    this->y = Y;
    this->speed = Speed;
    this->_path = path;

    // Create and load texture
    _texture = new Texture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        this->width = _texture->getWidth();
        this->height = _texture->getHeight();
    }
}

/**
 * @brief Copy constructor for the Player class.
 * Creates a new Player object by copying the properties of another Player object.
 * Loads the texture from the specified file path.
 * @param player The Player object to be copied.
 */
Player::Player(const Player& player) {
    // Copy player properties
    this->x = player.x;
    this->y = player.y;
    this->speed = player.speed;
    this->_path = player._path;

    // Create and load texture
    _texture = new Texture();
    if (!_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        this->width = _texture->getWidth();
        this->height = _texture->getHeight();
    }
}

/**
 * @brief Destructor for the Player class.
 * Frees the texture resources and deletes the texture object.
 */
Player::~Player() {
    _texture->free();
    delete _texture;
}

//Getters

/**
 * @brief Getter for the X position of the player.
 * @return The X position of the player.
 */
float Player::getX() {
    return this->x;
}

/**
 * @brief Getter for the Y position of the player.
 * @return The Y position of the player.
 */
float Player::getY() {
    return this->y;
}

/**
 * @brief Getter for the width of the player's texture.
 * @return The width of the player's texture.
 */
float Player::getWidth() {
    return this->width;
}

/**
 * @brief Getter for the height of the player's texture.
 * @return The height of the player's texture.
 */
float Player::getHeight() {
    return this->height;
}

/**
 * @brief Getter for the speed of the player.
 * @return The speed of the player.
 */
float Player::getSpeed() {
    return this->speed;
}


//Setters

/**
 * @brief Setter for the X position of the player.
 * @param X The new X position of the player.
 */
void Player::setX(float X) {
    this->x = X;
}

/**
 * @brief Setter for the Y position of the player.
 * @param Y The new Y position of the player.
 */
void Player::setY(float Y) {
    this->y = Y;
}

/**
 * @brief Setter for the width of the player's texture.
 * @param Width The new width of the player's texture.
 */
void Player::setWidth(float Width) {
    this->width = Width;
}

/**
 * @brief Setter for the height of the player's texture.
 * @param Height The new height of the player's texture.
 */
void Player::setHeight(float Height) {
    this->height = Height;
}

/**
 * @brief Setter for the speed of the player.
 * @param Speed The new speed of the player.
 */
void Player::setSpeed(float Speed) {
    this->speed = Speed;
}

//Methods

/**
 * @brief Handles SDL events for the player.
 * Adjusts the player's speed based on the key events.
 * @param sdlEvent The SDL event to handle.
 */
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

/**
 * @brief Renders the player's texture on the screen.
 */
void Player::render() {
    // Show the texture
    _texture->render((int)this->getX(), (int)this->getY());
}

/**
 * @brief Sets a new texture for the player.
 * Loads the texture from the specified file path and updates the player's dimensions.
 * @param _path The new file path of the texture to load.
 */
void Player::setTexture(std::string _path) {
    this->_texture->free();
    this->_texture = new Texture();
    if (!this->_texture->loadFromFile(_path)) {
        printf("Failed to load the texture!\n");
    }
    else {
        this->width = this->_texture->getWidth();
        this->height = this->_texture->getHeight();
    }
}