#include "../HeaderFiles/Collisions.h"
#include "../HeaderFiles/Constants.h"

void CheckCollisions(Player& player, Block levels[][NUM_BLOCKS], Ball& ball) {

    //Verify collisions between Blocks and Ball
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_BLOCKS; j++) {
            if (!levels[i][j].getDestroyed()) {
                if (ball.getX() < levels[i][j].getX() + BLOCK_WIDTH && ball.getX() + ball.getRadius() * 2 > levels[i][j].getX() &&
                    ball.getY() < levels[i][j].getY() + BLOCK_HEIGHT && ball.getY() + ball.getRadius() * 2 > levels[i][j].getY()) {
                    ball.InvertVelY();
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
    if (ball.getX() - ball.getRadius() < 0 || ball.getX() + ball.getRadius() > SCREEN_WIDTH) {
        ball.InvertVelX();
    }
    if (ball.getY() - ball.getRadius() < 0 || ball.getY() + ball.getRadius() > SCREEN_HEIGHT) {
        ball.InvertVelY();
    }

}