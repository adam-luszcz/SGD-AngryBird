#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->Init("Angry Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
    //SDL_TimerID timerId = SDL_AddTimer(5000, &Game::RenderScoreHandler, &game);
    while (game->Running()) {

        frameStart = SDL_GetTicks();

        game->HandleEvents();
        game->Update();
        game->Render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    delete game;
    //SDL_RemoveTimer(timerId);

    return 0;
}
