#include "../HeaderFiles/Texture.h"
#include "../HeaderFiles/Globals.h"
#include "../HeaderFiles/Constants.h"
#include <SDL_image.h>
#include <SDL_ttf.h>


Texture::Texture() {
    // Initialize
    this->_texture = NULL;
    this->_width = 0;
    this->_height = 0;

    this->_surfacePixels = NULL;
    this->_rawPixels = NULL;
    this->_rawPitch = 0;
}

Texture::Texture(std::string path) {
    // Initialize
    this->_texture = NULL;
    this->_width = 0;
    this->_height = 0;

    this->_surfacePixels = NULL;
    this->_rawPixels = NULL;
    this->_rawPitch = 0;

    loadFromFile(path);
}

Texture::~Texture() {
    // Deallocate existing assets
    free();
}

bool Texture::loadFromFile(std::string path) {
    // Load pixels
    if (!loadPixelsFromFile(path)) {
        printf("Failed to load pixels for %s!\n", path.c_str());
    }
    else {
        // Load texture from pixels
        if (!loadFromPixels()) {
            printf("Failed to texture from pixels from %s!\n", path.c_str());
        }
    }

    // Return success
    return _texture != NULL;
}

bool Texture::loadPixelsFromFile(std::string path) {
    // Free preexisting assets
    free();

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else {
        // Convert surface to display format
        _surfacePixels = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, 0);
        if (_surfacePixels == NULL) {
            printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        }
        else {
            // Get image dimensions
            _width = _surfacePixels->w;
            _height = _surfacePixels->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return _surfacePixels != NULL;
}

bool Texture::loadFromPixels() {
    // Only load if pixels exist
    if (_surfacePixels == NULL) {
        printf("No pixels loaded!");
    }
    else {
        // Color key image
        SDL_SetColorKey(_surfacePixels, SDL_TRUE, SDL_MapRGB(_surfacePixels->format, 0, 0xFF, 0xFF));

        // Create texture from surface pixels
        _texture = SDL_CreateTextureFromSurface(globalRenderer, _surfacePixels);
        if (_texture == NULL) {
            printf("Unable to create texture from loaded pixels! SDL Error: %s\n", SDL_GetError());
        }
        else {
            // Get image dimensions
            _width = _surfacePixels->w;
            _height = _surfacePixels->h;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(_surfacePixels);
        _surfacePixels = NULL;
    }

    // Return success
    return _texture != NULL;
}

bool Texture::createBlank(int width, int height, SDL_TextureAccess access) {
    // Get rid of preexisting texture
    free();

    // Create uninitialized texture
    _texture = SDL_CreateTexture(globalRenderer, SDL_PIXELFORMAT_RGBA8888, access, width, height);
    if (_texture == NULL) {
        printf("Unable to create streamable blank texture! SDL Error: %s\n", SDL_GetError());
    }
    else {
        _width = width;
        _height = height;
    }

    return _texture != NULL;
}

void Texture::free() {
    // Free texture if it exists
    if (_texture != NULL) {
        SDL_DestroyTexture(_texture);
        _texture = NULL;
        _width = 0;
        _height = 0;
    }

    // Free surface if it exists
    if (_surfacePixels != NULL) {
        SDL_FreeSurface(_surfacePixels);
        _surfacePixels = NULL;
    }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    // Modulate texture rgb
    SDL_SetTextureColorMod(_texture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending) {
    // Set blending function
    SDL_SetTextureBlendMode(_texture, blending);
}

void Texture::setAlpha(Uint8 alpha) {
    // Modulate texture alpha
    SDL_SetTextureAlphaMod(_texture, alpha);
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    // Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, _width, _height };

    // Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    // Render to screen
    SDL_RenderCopyEx(globalRenderer, _texture, clip, &renderQuad, angle, center, flip);
}

void Texture::renderCopyEx(SDL_Rect* destinationRect, SDL_Rect* clipRect, double angle, SDL_Point* center, SDL_RendererFlip flip) {
    // Render to screen
    SDL_RenderCopyEx(globalRenderer, _texture, clipRect, destinationRect, angle, center, flip);
}

void Texture::setAsRenderTarget() {
    // Make self render target
    SDL_SetRenderTarget(globalRenderer, _texture);
}

int Texture::getWidth() {
    return _width;
}

int Texture::getHeight() {
    return _height;
}

Uint32* Texture::getPixels32() {
    Uint32* pixels = NULL;

    if (_surfacePixels != NULL) {
        pixels = static_cast<Uint32*>(_surfacePixels->pixels);
    }

    return pixels;
}

Uint32 Texture::getPixel32(Uint32 x, Uint32 y) {
    // Convert the pixels to 32 bit
    Uint32* pixels = static_cast<Uint32*>(_surfacePixels->pixels);

    // Get the pixel requested
    return pixels[(y * getPitch32()) + x];
}

Uint32 Texture::getPitch32() {
    Uint32 pitch = 0;

    if (_surfacePixels != NULL) {
        pitch = _surfacePixels->pitch / 4;
    }

    return pitch;
}

bool Texture::lockTexture() {
    bool success = true;

    // Texture is already locked
    if (_rawPixels != NULL) {
        printf("Texture is already locked!\n");
        success = false;
    }
    // Lock texture
    else {
        if (SDL_LockTexture(_texture, NULL, &_rawPixels, &_rawPitch) != 0) {
            printf("Unable to lock texture! %s\n", SDL_GetError());
            success = false;
        }
    }

    return success;
}

bool Texture::unlockTexture() {
    bool success = true;

    // Texture is not locked
    if (_rawPixels == NULL) {
        printf("Texture is not locked!\n");
        success = false;
    }
    // Unlock texture
    else {
        SDL_UnlockTexture(_texture);
        _rawPixels = NULL;
        _rawPitch = 0;
    }

    return success;
}

void Texture::copyRawPixels32(void* pixels) {
    // Texture is locked
    if (_rawPixels != NULL) {
        // Copy to locked pixels
        memcpy(_rawPixels, pixels, _rawPitch * _height);
    }
}
