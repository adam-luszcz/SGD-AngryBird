#include "DynamicText.h"
#include <iostream>

bool DynamicText::ttfInitialized = false;

DynamicText::DynamicText(std::string fontfilepath, size_t fontSize){

    if(!ttfInitialized && TTF_Init() == -1){
        std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
    }else{
        //std::cout << "SDL2_ttf system ready to go!" << std::endl;

        ttfInitialized = true;
    }
    font = TTF_OpenFont(fontfilepath.c_str(), fontSize);
    if(font == nullptr){
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }
}

DynamicText::~DynamicText(){
    SDL_DestroyTexture(textTex);
    TTF_CloseFont(font);
}

void DynamicText::DrawText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h){
    textSurface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
    textTex = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    textRect.x = x;
    textRect.y = y;
    textRect.w = w;
    textRect.h = h;
    SDL_RenderCopy(renderer, textTex, NULL, &textRect);
    if(textTex != nullptr){
        SDL_DestroyTexture(textTex);
    }

}