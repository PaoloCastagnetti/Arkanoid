#include "Functions.h";
#include "HeaderFiles/Constants.h"

int RandomNumForBlock(int first, int last) {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Crea una distribuzione uniforme tra 1 e 5
    std::uniform_int_distribution<int> dis(first, last);

    // Genera un numero casuale tra 1 e 5
    int randomNum = dis(gen);
    return randomNum;
}

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

void resetPositions(Player& player, Ball& ball) {
    player.setX(SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2);
    player.setY(SCREEN_HEIGHT - PLAYER_HEIGHT - 10);

    ball.setX(SCREEN_WIDTH / 2);
    ball.setY(SCREEN_HEIGHT / 2);
}