#include "Player.h"
#include "TextureManager.h"
#include "vector"

const int SHOTGUN_RECOIL = 5;

std::vector<SDL_Rect> walls;


Player::Player(const char* filename, SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    playerTex = TextureManager::LoadTexture(filename, renderer);
    walls.push_back({0, 0, 30, 600});
    walls.push_back({0, 0, 800, 30});
    walls.push_back({770, 0, 30, 600});
    walls.push_back({0, 570, 800, 30});

    xpos = x;
    ypos = y;

    destRect.h = destRect.w = srcRect.h = srcRect.w = 32;
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

}

void Player::Render() {
    SDL_RenderCopyEx(renderer, playerTex, &srcRect, &destRect, angle, nullptr, SDL_FLIP_NONE);
}

void Player::Clean() {
    SDL_DestroyTexture(playerTex);
}

void Player::HandleEvent(SDL_Event& e) {
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

void Player::HandleWallCollisions() {

}

bool Player::CheckCollision(SDL_Rect a, SDL_Rect b) {
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        return false;
    }

    return true;
}