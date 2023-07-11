/**
 * @file Functions.cpp
 * @brief Implementation file for helper functions.
 */

#include "Functions.h";
#include "HeaderFiles/Constants.h"

 /**
  * @brief Generates a random integer within the specified range.
  * @param first The lower bound of the range.
  * @param last The upper bound of the range.
  * @return A random integer within the specified range.
  */
int RandomNumForBlock(int first, int last) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dis(first, last);

    int randomNum = dis(gen);
    return randomNum;
}

/**
 * @brief Checks if all blocks in the game are destroyed.
 * @param levels The array of blocks.
 * @return True if all blocks are destroyed, false otherwise.
 */
bool allBlocksDestroyed(Block** levels) {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_BLOCKS; ++j) {
            if (!levels[i][j].getDestroyed()) {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Resets the positions of the player and the ball to their initial values.
 * @param player The player object.
 * @param ball The ball object.
 */
void resetPositions(Player& player, Ball& ball) {
    player.setX(SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2);
    player.setY(SCREEN_HEIGHT - PLAYER_HEIGHT - 10);

    ball.setX(SCREEN_WIDTH / 2);
    ball.setY(SCREEN_HEIGHT / 2);
}

/**
 * @brief Loads the levels of the game.
 * Sets the positions, textures, and destroyed states of the blocks based on the current level.
 * @param levels The array of blocks.
 * @param currentLevel The current level of the game.
 */
void loadLevels(Block** levels, int currentLevel) {
    std::string path;
    int tmp_val = 0;

    int start = 0, range = 0;
    if (currentLevel == 0) {
        start = 1;
        range = 3;
    }
    else if (currentLevel == 1) {
        start = 2;
        range = 4;
    }
    else if (currentLevel == 2) {
        start = 3;
        range = 5;
    }


    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_BLOCKS; j++) {
            levels[i][j].setX(j * (BLOCK_WIDTH + 10) + 50);
            levels[i][j].setY(i * (BLOCK_HEIGHT + 10) + 50);
            tmp_val = RandomNumForBlock(start, range);
            switch (tmp_val) {
            case 1:
                path = YELLOW_BLOCK;
                break;
            case 2:
                path = GREEN_BLOCK;
                break;
            case 3:
                path = ORANGE_BLOCK;
                break;
            case 4:
                path = BLU_BLOCK;
                break;
            case 5:
                path = RED_BLOCK;
                break;
            default:
                printf("Error: Block color assignment");
                break;
            }
            levels[i][j].setTexture(path);
            levels[i][j].setDestroyed(false);
        }
    }
}

/**
 * @brief Handles the input events from the user.
 * Updates the player's position based on the keyboard input.
 * @param player The player object.
 */
void handleInput(Player& player) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            exit(0);
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                player.setX(player.getX() - player.getSpeed());
                if (player.getX() < 0) {
                    player.setX(0);
                }
                break;
            case SDLK_RIGHT:
                player.setX(player.getX() + player.getSpeed());
                if (player.getX() + player.getWidth() > SCREEN_WIDTH) {
                    player.setX(SCREEN_WIDTH - player.getWidth());
                }
                break;
            }
        }
    }
}