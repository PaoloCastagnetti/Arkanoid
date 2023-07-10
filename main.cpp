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
#include "HeaderFiles/MGDTexture.h"
#include "Functions.h"

// Global variables
SDL_Window* globalWindow = nullptr;
SDL_Renderer* globalRenderer = nullptr;
Mix_Music* globalMusic = nullptr;

//Background
MGDTexture* backgroundTexture;

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
    globalWindow = SDL_CreateWindow("ARKANOID", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
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

    //Initialize background
    backgroundTexture = new MGDTexture("Assets/Arkanoid_Background.png");

    return true;
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
bool update(Player& player, Ball& ball, Block** levels) {
    bool dead = false;

    handleInput(player);

    dead = CheckCollisions(player, ball, levels);

    ball.Update();

    return dead;
}

// Game objects rendering
void render(Player& player, Ball& ball, Block** levels) {
    SDL_SetRenderDrawColor(globalRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(globalRenderer);

    SDL_Rect rectDest = { 0, 0, 600, 600};
    backgroundTexture->renderCopyEx(&rectDest);

    // Player rendering
    player.render();

    // Blocks rendering
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_BLOCKS; ++j) {
            if (!levels[i][j].getDestroyed()) {
                levels[i][j].render();
            }
        }
    }
    
    //Ball rendering
    ball.render();

    // Update screen
    SDL_RenderPresent(globalRenderer);
}

// Main function of the game
void runGame() {
    
    //Player definition
    float player_X = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    float player_Y = SCREEN_HEIGHT - PLAYER_HEIGHT - 10;
    float player_S = PLAYER_SPEED;
    Player* player = new Player(player_X, player_Y, player_S, "Assets/Bars/Arkanoid_LongBar.png");

    //Ball definition
    float ballX = SCREEN_WIDTH / 2;
    float ballY = SCREEN_HEIGHT / 2; 
    float ballRadius = 12;
    float ballVelX = 0.05f;
    float ballVelY = 0.05f;
    Ball* ball = new Ball(ballX, ballY, ballRadius, ballVelX, ballVelY, "Assets/Arkanoid_RedBall.png");

    int currentLevel = 0; // Indice del livello corrente
    std::string texturePath;

    Block** levels = new Block * [NUM_ROWS];
    for (int i = 0; i < NUM_ROWS; i++) {
        levels[i] = new Block[NUM_BLOCKS];
    }

    loadLevels(levels, currentLevel);

    bool quit = false;

    while (!quit) {
        
        quit = update(*player, *ball, levels);
        
        render(*player, *ball, levels);

        if (allBlocksDestroyed(levels)) {
            // Get to the next level
            ++currentLevel;
            if (currentLevel > 2) {
                // Hai completato tutti i livelli, fai qualcosa come mostrare un messaggio di vittoria o ricominciare dal primo livello
            }
            else {
                // Load new level
                loadLevels(levels, currentLevel);
                
                resetPositions(*player, *ball);

                if (currentLevel == 1) {
                    texturePath = "Assets/Bars/Arkanoid_MediumBar.png";
                    ball->setVelocityX(0.06f);
                    ball->setVelocityY(0.06f);
                    player->setSpeed(22.5f);
                }
                else if (currentLevel == 2) {
                    texturePath = "Assets/Bars/Arkanoid_ShortBar.png";
                    ball->setVelocityX(0.07f);
                    ball->setVelocityY(0.07f);
                    player->setSpeed(25.f);
                }
                player->setTexture(texturePath);
            }
        }
    }

    delete player;
    delete ball;
    delete backgroundTexture;
    
    // Deallocation of rows
    for (int i = 0; i < NUM_ROWS; i++) {
        delete[] levels[i];
    }
    // Deallocation of main array
    delete[] levels;
    
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
