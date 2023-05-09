#ifndef ANGRYBIRD_PLAYER_H
#define ANGRYBIRD_PLAYER_H



#include "Game.h"

class Player {
public:
    Player(const char* filename, SDL_Renderer* ren, int x, int y);
    ~Player();

    void Update();
    void Render();
    void Clean();

private:
    int xpos, ypos;

    SDL_Texture* playerTex;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
};

#endif //ANGRYBIRD_PLAYER_H