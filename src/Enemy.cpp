#include "Enemy.h"
#include "TextureManager.h"
#include <iostream>



Enemy::Enemy(const char *filename, SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    enemyTex = TextureManager::LoadTexture(filename, renderer);
    xpos = x;
    ypos = y;
    destRect.h = destRect.w = srcRect.h = srcRect.w = 32;
    srcRect.x = srcRect.y = 0;
}

Enemy::~Enemy() {
    Clean();
    std::cout << "Enemy deleted!" << std::endl;
}

void Enemy::Update() {
    xpos -= velocityX;

    destRect.x = xpos;
    destRect.y = ypos;
}

void Enemy::Render() {
    SDL_RenderCopy(renderer, enemyTex, &srcRect, &destRect);
}

void Enemy::Clean() {
    SDL_DestroyTexture(enemyTex);
}

SDL_Rect Enemy::GetDestRect() {
    return destRect;
}