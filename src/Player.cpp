#include "Player.h"
#include "TextureManager.h"
#include "vector"
#include <iostream>

const int SHOTGUN_RECOIL = 5;
const int MAX_SPEED = 20;

std::vector<SDL_Rect> walls;


Player::Player(const char* filename, SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    playerTex = TextureManager::LoadTexture(filename, renderer);
    walls.push_back({0, 0, 30, 600}); // left
    walls.push_back({0, 0, 800, 30}); // top
    walls.push_back({770, 0, 30, 600}); // right
    walls.push_back({0, 570, 800, 30}); // bottom

    xpos = x;
    ypos = y;

    destRect.h = destRect.w = srcRect.h = srcRect.w = 32;
    srcRect.x = srcRect.y = 0;

    angle = 0;
    velocityX = velocityY = 0;
}

Player::~Player() {
    Clean();
    std::cout << "Player deleted!" << std::endl;
}

void Player::Update() {
    HandleWallCollisions();
    if (velocityX > MAX_SPEED) {
        velocityX = MAX_SPEED;
    }
    if (velocityY > MAX_SPEED) {
        velocityY = MAX_SPEED;
    }
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
    // corner handling
    if ((CheckCollision(destRect, walls[0]) && CheckCollision(destRect, walls[1])) ||
    (CheckCollision(destRect, walls[1]) && CheckCollision(destRect, walls[2])) ||
    (CheckCollision(destRect, walls[2]) && CheckCollision(destRect, walls[3])) ||
    (CheckCollision(destRect, walls[3]) && CheckCollision(destRect, walls[0]))) {
        velocityX = -velocityX;
        velocityY = -velocityY;
    }
    // left wall
    else if (CheckCollision(destRect, walls[0])) {
        if (velocityY > destRect.y) {
            velocityY = -velocityY;
        }
        xpos += 4;
        velocityX = -velocityX;
    }
    // right wall
    else if (CheckCollision(destRect, walls[2])) {
        if (velocityY > destRect.y) {
            velocityY = -velocityY;
        }
        xpos -= 4;
        velocityX = -velocityX;
    }
    // top wall
    else if (CheckCollision(destRect, walls[1])) {
        if (velocityX > destRect.x) {
            velocityX = -velocityX;
        }
        ypos += 4;
        velocityY = -velocityY;
    }
    // bottom wall
    else if (CheckCollision(destRect, walls[3])) {
        if (velocityX > destRect.x) {
            velocityX = -velocityX;
        }
        ypos -= 4;
        velocityY = -velocityY;
    }
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