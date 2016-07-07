//
//  renderer.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 25-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef renderer_hpp
#define renderer_hpp

#include <stdio.h>

#include "projectmain.hpp"

using namespace std;

namespace renderer {
    
    extern GLuint glProgram;
    
    extern GLuint glUniform_texture;
    
    extern GLuint glAttrib_position;
    extern GLuint glAttrib_color;
    extern GLuint glAttrib_textureCoords;
    
    
    bool initializeRenderer();
    void cleanup();
    
    void setUniforms();
    
    void glRenderRect(SDL_Color color, float posX, float posY, float width, float height);
    void glRenderCircle(SDL_Color color, float posX, float posY, float width, float height);
    
    /*
    void renderRectangle(float posx, float posy, float sizex, float sizey, SDL_Color color);
    void renderRectangle(SDL_Rect rect, SDL_Color color);
    
    void renderTexture(SDL_Texture *texture, SDL_Color *color, float posx, float posy, float sizex, float sizey);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, SDL_Rect *rect);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, float posx, float posy, float sizex, float sizey, float angle, float rposx, float rposy);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, float posx, float posy, float sizex, float sizey, float angle, SDL_Point *rpoint);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, SDL_Rect *rect, const float rotationangle, SDL_Point *rotationpoint);
    */
    
    void renderText(TTF_Font* font, std::string str, int posx, int posy, SDL_Color color);
    
}

#endif /* renderer_hpp */
