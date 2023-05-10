#include "TextureManager.h"
#include "Player.h"
#include "Game.h"
#include <iostream>

SDL_Texture* bgTex;
Player* player;

Game::Game() {}

Game::~Game() {
    Clean();
    std::cout << "Game deleted!" << std::endl;
}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, x, y, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer,255, 0, 0, 255);
        }
        isRunning = true;
    }

    bgTex = TextureManager::LoadTexture("assets/bg_new.png", renderer);
    player = new Player("assets/player/bird.png", renderer, 400 - 38, 300 - 28);
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
}

void Game::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgTex, NULL, NULL);
    player->Render();
    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyTexture(bgTex);
    delete player;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}