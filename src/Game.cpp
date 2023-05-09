#include "TextureManager.h"

SDL_Texture* bgTex;

Game::Game() {}

Game::~Game() {}

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
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

    bgTex = TextureManager::LoadTexture("assets/bg.png", renderer);
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {}

void Game::render() {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, bgTex, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}