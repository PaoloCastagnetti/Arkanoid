#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdint.h>
#include "HeaderFiles/Player.h"
#include "HeaderFiles/Ball.h"
#include "HeaderFiles/Block.h"
#include "HeaderFiles/Constants.h"
#include "HeaderFiles/Timer.h"
#include "HeaderFiles/Collisions.h"
#include "HeaderFiles/Globals.h"
#include "HeaderFiles/Texture.h"

// Global variables
SDL_Window* globalWindow = nullptr;
SDL_Renderer* globalRenderer = nullptr;
Mix_Music* globalMusic = nullptr;

// Initialize SDL and the game window
bool init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    Uint32 windowFlags = SDL_WindowFlags::SDL_WINDOW_SHOWN;

    // Create window
    globalWindow = SDL_CreateWindow("MGD Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (globalWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer for window
    globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED);
    if (globalRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    // Load music
    globalMusic = Mix_LoadMUS("Assets/BG_Music.mp3");
    if (globalMusic == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    if (Mix_PlayMusic(globalMusic, -1) == -1) {
        printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    // Initialize the renderer blend mode
    SDL_SetRenderDrawBlendMode(globalRenderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);

    // Initialize renderer color
    SDL_SetRenderDrawColor(globalRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
    
    //Background creation and rendering
    Texture* backgroundTexture = new Texture("Assets/Arkanoid_Background.png");
    
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

        SDL_Rect rectDest = { 0, 0, 800, 600 };
        //backgroundTexture->renderCopyEx(&rectDest);
        backgroundTexture->render();
    }

    delete player;
    delete ball;
    delete backgroundTexture;
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
