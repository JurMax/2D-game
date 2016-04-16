//
//  baseobjects.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "baseobjects.hpp"




void BaseObject::render(SDL_Renderer *renderer) {
    SDL_Rect rect;
    rect.x = posX;
    rect.y = posY;
    rect.w = width;
    rect.h = height;
    
    SDL_SetRenderDrawColor(renderer, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
    SDL_RenderFillRect(renderer, &rect);
}


BaseObject createBaseObject(float posx, float posy, float wdth, float hght) {
    BaseObject object;
    object.posX = posx;
    object.posY = posy;
    object.width = wdth;
    object.height = hght;
    return object;
}
