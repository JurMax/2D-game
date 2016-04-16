//
//  baseobjects.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef baseobjects_hpp
#define baseobjects_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class BaseObject {
public:
    float posX = 0;
    float posY = 0;
    
    float velocityX = 0;
    float velocityY = 0;
    
    float width = 0;
    float height = 0;
    
    SDL_Color debugColor = { 255, 255, 255 };
    
    bool onGround = false;
    bool pushOut = true;  /* is impassable */
    
    void update();
    void render(SDL_Renderer *renderer);
    
};

BaseObject createBaseObject(float posx, float posy, float wdth, float hght);



class Rectangle: public BaseObject {
};



#endif /* baseobjects_hpp */
