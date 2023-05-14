// Source: https://github.com/MikeShah/SDL2_Tutorials/tree/main/29_FontClass

#ifndef ANGRYBIRD_DYNAMICTEXT_H
#define ANGRYBIRD_DYNAMICTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
class DynamicText{
public:

    DynamicText(std::string fontfilepath, size_t fontSize);
    ~DynamicText();
    void DrawText(SDL_Renderer* renderer, std::string text,int x, int y, int w, int h);

private:
    SDL_Rect textRect;
    SDL_Texture* textTex;
    SDL_Surface* textSurface;

    TTF_Font* font;

    static bool ttfInitialized;

};


#endif //ANGRYBIRD_DYNAMICTEXT_H
