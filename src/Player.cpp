#include "Player.h"
#include "TextureManager.h"

const int SHOTGUN_RECOIL = 5;

Player::Player(const char* filename, SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    playerTex = TextureManager::LoadTexture(filename, renderer);
    xpos = x;
    ypos = y;

    srcRect.h = srcRect.w = 32;
    srcRect.x = srcRect.y = 0;

    angle = 0;
    velocityX = velocityY = 0;

}

Player::~Player() {}

void Player::Update() {
    xpos += velocityX;
    ypos += velocityY;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}

void Player::Render() {
    SDL_RenderCopyEx(renderer, playerTex, &srcRect, &destRect, angle, nullptr, SDL_FLIP_NONE);
}

void Player::Clean() {
    SDL_DestroyTexture(playerTex);
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        double dx = mouseX - (xpos + srcRect.w / 2);
        double dy = mouseY - (ypos + srcRect.h / 2);
        double angleRadians = atan2(dy, dx);

        velocityX -= SHOTGUN_RECOIL * cos(angleRadians);
        velocityY -= SHOTGUN_RECOIL * sin(angleRadians);
    } else if (e.type == SDL_MOUSEMOTION) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        double dx = mouseX - (xpos + srcRect.w / 2);
        double dy = mouseY - (ypos + srcRect.h / 2);
        angle = atan2(dy, dx) * 180 / M_PI;
    }
}