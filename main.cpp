#include <SDL.h>
#include <stdint.h>
#include "HeaderFiles/Player.h"
#include "HeaderFiles/Ball.h"
#include "HeaderFiles/Block.h"
#include "HeaderFiles/Constants.h"
#include "HeaderFiles/Timer.h"
#include "HeaderFiles/Collisions.h"
#include "HeaderFiles/Globals.h"

// Global variables
SDL_Window* globalWindow = nullptr;
SDL_Renderer* globalRenderer = nullptr;

// Initialize SDL and the game window
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    globalWindow = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (globalWindow == nullptr) {
        return false;
    }

    globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED);
    if (globalRenderer == nullptr) {
        return false;
    }

    return true;
}

// Carica i livelli di gioco
void loadLevels(Block levels[][NUM_BLOCKS]) {
    // Livello 1
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_BLOCKS; j++) {
            levels[i][j].setX(j * (BLOCK_WIDTH + 5) + 50);
            levels[i][j].setY(i * (BLOCK_HEIGHT + 5) + 50);
            levels[i][j].setDestroyed(false);
        }
    }

    // Livello 2
    // ...

    // Livello 3
    // ...
}

// Gestisci l'input del giocatore
void handleInput(Player& player) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            // L'utente ha chiuso la finestra
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

// Game update
bool update(Player& player, Ball& ball, Block levels [][NUM_BLOCKS]) {
    
    Timer stepTimer;
    // Get the delta time in milliseconds
    Uint32 deltaTime = stepTimer.getTicks();
    // Calculate the delta time in seconds
    double deltaTimeF = deltaTime * 0.001;

    // Restart step timer
    stepTimer.start();

    bool dead = CheckCollisions(player, ball, levels);
    ball.Update();
    return dead;
}

// Game objects rendering
void render(Player& player, Ball& ball, Block levels [][NUM_BLOCKS]) {
    SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
    SDL_RenderClear(globalRenderer);

    // Player rendering
    SDL_SetRenderDrawColor(globalRenderer, 255, 255, 255, 255);
    SDL_Rect playerRect = { player.getX(), player.getY(), player.getWidth(), player.getHeight()};
    SDL_RenderFillRect(globalRenderer, &playerRect);

    // Blocks rendering
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    int k = 0;
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_BLOCKS; ++j) {
            if (!levels[i][j].getDestroyed()) {
                if (k < (TOTAL_N_BLOCKS/3)) {
                    r = 255; g = 0; b = 0;
                }
                else if (k < (TOTAL_N_BLOCKS / 3) * 2){
                    r = 0; g = 0; b = 255;
                }
                else {
                    r = 0; g = 255; b = 0;
                }
                SDL_SetRenderDrawColor(globalRenderer, r, g, b, 255);
                SDL_Rect blockRect = { levels[i][j].getX(), levels[i][j].getY(), BLOCK_WIDTH, BLOCK_HEIGHT};
                SDL_RenderFillRect(globalRenderer, &blockRect);
                ++k;
            }
        }
    }

    //Ball rendering
    SDL_SetRenderDrawColor(globalRenderer, 255, 255, 255, 255);
    SDL_Rect ballRect = { ball.getX() - ball.getRadius(), ball.getY() - ball.getRadius(), ball.getRadius() * 2, ball.getRadius() * 2};
    SDL_RenderFillRect(globalRenderer, &ballRect);
    SDL_RenderPresent(globalRenderer);
}

// Main function of the game
void runGame() {
    
    //Player definition
    float player_X = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    float player_Y = SCREEN_HEIGHT - PLAYER_HEIGHT - 10;
    float player_W = PLAYER_WIDTH;
    float player_H = PLAYER_HEIGHT;
    float player_S = PLAYER_SPEED;
    Player* player = new Player(player_X, player_Y, player_W, player_H, player_S);

    //Ball definition
    float ballX = SCREEN_WIDTH / 2;
    float ballY = SCREEN_HEIGHT / 2; 
    float ballRadius = 5;
    float ballVelX = 0.05;
    float ballVelY = 0.05;
    Ball* ball = new Ball(ballX, ballY, ballRadius, ballVelX, ballVelY);

    Block levels[NUM_ROWS][NUM_BLOCKS];
    loadLevels(levels);

    bool quit = false;

    while (!quit) {
        handleInput(*player);
        quit = update(*player, *ball, levels);
        
        render(*player, *ball, levels);
    }

    delete(player);
    delete(ball);
}

// Free resources and close game
void close() {
    SDL_DestroyRenderer(globalRenderer);
    SDL_DestroyWindow(globalWindow);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        return -1;
    }

    runGame();

    close();

    return 0;
}
