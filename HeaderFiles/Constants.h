#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// Costants for the game screen
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

// Costants for the game bar
const float PLAYER_WIDTH = 160.f;
const float PLAYER_HEIGHT = 24.f;
const float PLAYER_SPEED = 20.f;

// Costants for the blocks
const int BLOCK_WIDTH = 64;
const int BLOCK_HEIGHT = 32;
const int NUM_BLOCKS = 7;
const int NUM_ROWS = 3;
const int TOTAL_N_BLOCKS = NUM_BLOCKS * NUM_ROWS;

// Costants for the blocks texture
const std::string BLU_BLOCK = "Assets/Blocks/Arkanoid_BluBlock.png";
const std::string GREEN_BLOCK = "Assets/Blocks/Arkanoid_GreenBlock.png";
const std::string RED_BLOCK = "Assets/Blocks/Arkanoid_RedBlock.png";
const std::string YELLOW_BLOCK = "Assets/Blocks/Arkanoid_YellowBlock.png";
const std::string ORANGE_BLOCK = "Assets/Blocks/Arkanoid_OrangeBlock.png";

#endif