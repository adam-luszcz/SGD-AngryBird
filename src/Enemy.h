#ifndef ANGRYBIRD_ENEMY_H
#define ANGRYBIRD_ENEMY_H

#include "Game.h"

class Enemy {
public:
    Enemy(const char* filename, SDL_Renderer* ren, int x, int y);
    ~Enemy();

    void Update();
    void Render();
    void Clean();

private:
    int xpos, ypos;
    int velocityX, velocityY;
    const int SPEED = 10;

    SDL_Texture* enemyTex;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
};


#endif //ANGRYBIRD_ENEMY_H
