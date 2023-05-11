#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "SDL_ttf.h"
#include "DynamicText.h"

SDL_Texture* bgTex;
Player* player;
std::vector<Enemy*> enemies;

Game::Game() {}

Game::~Game() {
    Clean();
    std::cout << "Game deleted!" << std::endl;
}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    int flags = 0;
    w = width;
    h = height;
    srand(std::time(nullptr));
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, x, y, w, h, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer,255, 0, 0, 255);
        }
        isRunning = true;
    }


    bgTex = TextureManager::LoadTexture("assets/bg_new.png", renderer);
    player = new Player("assets/player/bird.png", renderer, 400 - 38, 300 - 28);
    scoreZone.w = w/2;
    scoreZone.h = h/2;
}

void Game::HandleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    player->HandleEvent(event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::Update() {
    player->Update();
    HandleEnemySpawn();
    for (auto enemy : enemies) {
        enemy->Update();
        HandleEnemyCollision(enemy);
    }
    HandleEnemyDestruction();
    AddScore();
}

void Game::Render(bool renderZone) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTex, NULL, NULL);
    DynamicText scoreText("assets/fonts/STENCIL.TTF", 32);
    scoreText.DrawText(renderer, "Score: " + std::to_string(score), w - 165, 25, w/6 ,h/6);
    player->Render();
    for (auto enemy : enemies) {
        enemy->Render();
    }
    RenderScoreZone();

    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyTexture(bgTex);
    delete player;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::RenderScoreZone() {
    if (SDL_GetTicks() % 300 == 0) {
        zoneIdx = rand() % 4;
        switch (zoneIdx) {
            case 0:
                scoreZone.x = scoreZone.y = 0;
                break;
            case 1:
                scoreZone.x = w / 2;
                scoreZone.y = 0;
                break;
            case 2:
                scoreZone.x = 0;
                scoreZone.y = h / 2;
                break;
            case 3:
                scoreZone.x = w / 2;
                scoreZone.y = h / 2;
                break;
        }
        //std::cout << zoneIdx << std::endl;
    }
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
    SDL_RenderFillRect(renderer, &scoreZone);
    SDL_RenderDrawRect(renderer, &scoreZone);
}

void Game::AddScore() {
    if (player->CheckCollision(player->GetDestRect(), scoreZone)) {
        score += 1;
        //std::cout << score << std::endl;
    }
}

void Game::HandleEnemyCollision(Enemy* e) {
    if (player->CheckCollision(player->GetDestRect(), e->GetDestRect())) {
        std::cout << "got hit!" << std::endl;
    }
}

void Game::HandleEnemySpawn() {
    int range = 540 - 30 + 1;
    int enemyYpos = rand() % range + 30;
    if (enemies.size() <= 10 && SDL_GetTicks() % 60 == 0) {
        enemies.push_back(new Enemy("assets/enemy/enemy_0.png", renderer, 800, enemyYpos));
    }
}
void Game::HandleEnemyDestruction() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->GetDestRect().x < 0) {
            enemies.erase(enemies.cbegin() + i);
        }
    }
    //std::cout << "enemies on screen: " << enemies.size() << std::endl;
}
