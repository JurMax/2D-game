//
//  functions.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "functions.hpp"


void renderText(SDL_Renderer *renderer, TTF_Font* font, char buffer[], int posx, int posy, SDL_Color color) {
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, buffer, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    int stringwidth = 0, stringheight = 0;
    TTF_SizeText(font, buffer, &stringwidth, &stringheight);
    
    SDL_Rect rect;
    rect.x = posx; rect.y = posy;
    rect.w = stringwidth; rect.h = stringheight;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
}
