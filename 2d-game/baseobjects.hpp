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

#include "projectmain.hpp"

class BaseObject {
public:
    float posX = 0;
    float posY = 0;
    float velocityX = 0;
    float velocityY = 0;
    float width = 0;
    float height = 0;
    
    int chunkID;
    
    GLuint vbo[2];
    GLuint vao[1];
    SDL_Color debugColor = { 255, 255, 255, 255 };
    
    bool onGround = false;
    bool pushOut = true;
    bool isMoving = false;

    bool updateGLBuffers = true;
    

    void update();
    void render();
    int collidesWith(BaseObject obj, float timePassed);
    
    void setBaseObject(float posx, float posy, float width, float height);
    void updateBuffers();
    
    void destroy();
    
};

BaseObject createBaseObject(float posx, float posy, float width, float height);


#endif /* baseobjects_hpp */


