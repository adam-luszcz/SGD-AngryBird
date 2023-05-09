#ifndef ANGRYBIRD_TEXTUREMANAGER_H
#define ANGRYBIRD_TEXTUREMANAGER_H

#endif //ANGRYBIRD_TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* filename, SDL_Renderer* renderer);
};