/**
 * @file Collisions.cpp
 * @brief Implementation file for collision detection functions.
 */

#include "../HeaderFiles/Collisions.h"
#include "../HeaderFiles/Constants.h"
#include <stdio.h>

 /**
  * @brief Checks for collisions between the player, ball, and blocks.
  * Updates the ball's velocity and destroys blocks if there is a collision.
  * @param player The player object.
  * @param ball The ball object.
  * @param levels The array of blocks.
  * @return True if the ball has collided with the bottom of the screen (game over), false otherwise.
  */
bool CheckCollisions(Player& player, Ball& ball, Block** levels) {

    //Verify collisions between Blocks and Ball
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_BLOCKS; j++) {
            if (!levels[i][j].getDestroyed()) {
                if (ball.getX() < levels[i][j].getX() + BLOCK_WIDTH && ball.getX() + ball.getRadius() * 2 > levels[i][j].getX() &&
                    ball.getY() < levels[i][j].getY() + BLOCK_HEIGHT && ball.getY() + ball.getRadius() * 2 > levels[i][j].getY()) {
                    // Check the side of the collision
                    bool touchedTop = ball.getY() + ball.getRadius() * 2 > levels[i][j].getY() && ball.getY() < levels[i][j].getY();
                    bool touchedBottom = ball.getY() < levels[i][j].getY() + BLOCK_HEIGHT && ball.getY() + ball.getRadius() * 2 > levels[i][j].getY() + BLOCK_HEIGHT;
                    bool touchedLeft = ball.getX() + ball.getRadius() * 2 > levels[i][j].getX() && ball.getX() < levels[i][j].getX();
                    bool touchedRight = ball.getX() < levels[i][j].getX() + BLOCK_WIDTH && ball.getX() + ball.getRadius() * 2 > levels[i][j].getX() + BLOCK_WIDTH;

                    // Reverse the speed of the ball based on the side of the collision
                    if (touchedTop || touchedBottom) {
                        ball.InvertVelY();
                    }
                    if (touchedLeft || touchedRight) {
                        ball.InvertVelX();
                    }
                    levels[i][j].setDestroyed(true);
                }
            }
        }
    }

    //Verify collisions between Player and Ball
    if (ball.getX() < player.getX() + PLAYER_WIDTH && ball.getX() + ball.getRadius() * 2 > player.getX() &&
        ball.getY() < player.getY() + PLAYER_HEIGHT && ball.getY() + ball.getRadius() * 2 > player.getY()) {
        ball.InvertVelY();
    }

    //Verify collisions between Screen and Ball
    if (ball.getX() - ball.getRadius() < 10 || (ball.getX() + ball.getRadius()) > (SCREEN_WIDTH-30)) {
        ball.InvertVelX();
    }
    if (ball.getY() - ball.getRadius() < 10 ) {
        ball.InvertVelY();
    }
    if (ball.getY() > SCREEN_HEIGHT) {
        return true;
        printf("MORTO");
    }
    return false;
}