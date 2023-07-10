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