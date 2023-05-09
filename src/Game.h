#ifndef ANGRYBIRD_GAME_H
#define ANGRYBIRD_GAME_H
#endif //ANGRYBIRD_GAME_H

#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

class Game {

public:
    Game();
    ~Game();

    void init(const char* title, int x, int y, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() {
        return isRunning;
    };

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
};