#pragma once
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// The window we'll be rendering to
extern struct SDL_Window* globalWindow;

// The window renderer
extern struct SDL_Renderer* globalRenderer;

// The music that will be played
extern Mix_Music* globalMusic;
