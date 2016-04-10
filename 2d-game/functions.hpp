//
//  functions.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "projectmain.hpp"


void renderText(SDL_Renderer *renderer, TTF_Font* font, char buffer[], int posx, int posy, SDL_Color color);

#endif /* functions_hpp */
