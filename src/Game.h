#ifndef ANGRYBIRD_GAME_H
#define ANGRYBIRD_GAME_H


#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

class Game {

public:
    Game();
    ~Game();

    void Init(const char* title, int x, int y, int width, int height, bool fullscreen);

    void HandleEvents();
    void Update();
    void Render(bool renderZone);
    void Clean();
    void RenderScoreZone();
    void AddScore();

    /*static Uint32 RenderScoreHandler(Uint32 interval, void *p) {
        Game *self = reinterpret_cast<Game *>(p);
        self->Render(true);
        return interval;
    }*/

    bool Running() {
        return isRunning;
    };
    int w, h;

private:
    int score = 0;
    bool isRunning;
    int zoneIdx;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Rect scoreZone;
};

#endif //ANGRYBIRD_GAME_H