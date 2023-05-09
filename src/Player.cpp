#include "Player.h"
#include "TextureManager.h"

Player::Player(const char* filename, SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    playerTex = TextureManager::LoadTexture(filename, renderer);
    xpos = x;
    ypos = y;

    srcRect.h = srcRect.w = 32;
    srcRect.x = srcRect.y = 0;



}

Player::~Player() {}

void Player::Update() {
    ypos += 2;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void Player::Render() {
    SDL_RenderCopy(renderer, playerTex, &srcRect, &destRect);
}

void Player::Clean() {
    SDL_DestroyTexture(playerTex);
}