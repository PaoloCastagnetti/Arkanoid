#include "../HeaderFiles/Collisions.h"
#include "../HeaderFiles/Constants.h"
#include <stdio.h>

bool CheckCollisions(Player& player, Ball& ball, Block levels[][NUM_BLOCKS]) {

    //Verify collisions between Blocks and Ball
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_BLOCKS; j++) {
            if (!levels[i][j].getDestroyed()) {
                if (ball.getX() < levels[i][j].getX() + BLOCK_WIDTH && ball.getX() + ball.getRadius() * 2 > levels[i][j].getX() &&
                    ball.getY() < levels[i][j].getY() + BLOCK_HEIGHT && ball.getY() + ball.getRadius() * 2 > levels[i][j].getY()) {
                    // Verifica il lato della collisione
                    bool touchedTop = ball.getY() + ball.getRadius() * 2 >= levels[i][j].getY() && ball.getY() <= levels[i][j].getY();
                    bool touchedBottom = ball.getY() <= levels[i][j].getY() + BLOCK_HEIGHT && ball.getY() + ball.getRadius() * 2 >= levels[i][j].getY() + BLOCK_HEIGHT;
                    bool touchedLeft = ball.getX() + ball.getRadius() * 2 >= levels[i][j].getX() && ball.getX() <= levels[i][j].getX();
                    bool touchedRight = ball.getX() <= levels[i][j].getX() + BLOCK_WIDTH && ball.getX() + ball.getRadius() * 2 >= levels[i][j].getX() + BLOCK_WIDTH;

                    // Inverti la velocità della pallina in base al lato della collisione
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
    if (ball.getX() - ball.getRadius() < 0 || ball.getX() + ball.getRadius() > SCREEN_WIDTH) {
        ball.InvertVelX();
    }
    if (ball.getY() - ball.getRadius() < 0 ) {
        ball.InvertVelY();
    }
    if (ball.getY() + ball.getRadius() > SCREEN_HEIGHT) {
        return true;
        printf("MORTO");
    }
    return false;

}