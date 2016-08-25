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
    
    extern GLuint glUniform_screenSize;
    extern GLuint glUniform_screenPos;
    extern GLuint glUniform_screenScale;
    extern GLuint glUniform_texture;
    extern GLuint glUniform_settings;
    
    extern GLuint glUniform_shapePos;
    extern GLuint glUniform_shapeRotation;
    extern GLuint glUniform_shapeRotationPoint;
    
    
    extern GLuint glAttrib_position;
    extern GLuint glAttrib_color;
    extern GLuint glAttrib_textureCoords;
    extern GLuint glAttrib_barycentric;
    
    
    bool initializeRenderer();
    void loadUniformLocation(GLuint *uniform, string location);
    void loadAttributeLocation(GLuint *attribute, string location);
    void cleanup();
    
    void setUniforms();
    
    void glRenderRect(SDL_Color color, float posX, float posY, float width, float height);
    void glRenderRect(GLuint texture, SDL_Color color, float posX, float posY, float width, float height, float rotation, float *rotX, float *rotY);
    void glRenderRect(GLuint texture, SDL_Color color, float posX, float posY, float width, float height);
    void glRenderCircle(SDL_Color color, float posX, float posY, float width, float height);
    
    void glRenderArrays(int points, GLfloat* vertices, GLfloat* colors, GLfloat* texturecoords, GLfloat* barycentric, GLuint texture);
    
    /*
    void renderRectangle(float posx, float posy, float sizex, float sizey, SDL_Color color);
    void renderRectangle(SDL_Rect rect, SDL_Color color);
    
    void renderTexture(SDL_Texture *texture, SDL_Color *color, float posx, float posy, float sizex, float sizey);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, SDL_Rect *rect);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, float posx, float posy, float sizex, float sizey, float angle, float rposx, float rposy);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, float posx, float posy, float sizex, float sizey, float angle, SDL_Point *rpoint);
    void renderTexture(SDL_Texture *texture, SDL_Color *color, SDL_Rect *rect, const float rotationangle, SDL_Point *rotationpoint);
    */
    
    void renderText(string str, SDL_Color color, float posX, float posY, float maxWidth, float lineHeight, bool alignleft);
    
}

#endif /* renderer_hpp */
