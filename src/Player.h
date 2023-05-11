#ifndef ANGRYBIRD_PLAYER_H
#define ANGRYBIRD_PLAYER_H



#include "Game.h"

class Player {
public:
    Player(const char* filename, SDL_Renderer* ren, int x, int y);
    ~Player();

    void Update();
    void Render();
    void Clean();
    void HandleEvent(SDL_Event& e);
    bool CheckCollision(SDL_Rect a, SDL_Rect b);
    void HandleWallCollisions();
    SDL_Rect GetDestRect();
private:
    int xpos, ypos;
    int velocityX, velocityY;
    double angle;

    SDL_Texture* playerTex;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
};

#endif //ANGRYBIRD_PLAYER_H