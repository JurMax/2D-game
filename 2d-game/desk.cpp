//
//  desk.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 21-08-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "desk.hpp"



namespace desk {
    
    vector<BaseObject> objects;

    
    float speedModifier = 0.8;
    float posx = 0;
    
    
    void create() {
        
    }


    void update() {
        if (world::isMoving) {
            posx += world::cameraSpeed - world::cameraSpeed * speedModifier;
            
            for (int i = 0; i < objects.size(); i++) {
                objects.at(i).posX += projectMain.cameraOffsetX - projectMain.cameraOffsetX*speedModifier;
            }
            if (posx + 50 < projectMain.cameraOffsetX) {
                posx = projectMain.cameraOffsetX + 120;
            }
        }
    }


    void render() {
        static float pos = 5, size = 1.5;
        static int dark = 250, light = 240;
        //renderer::glRenderRect(r::texture_Noise, {(Uint8)light,(Uint8)light,(Uint8)light,255}, projectMain.cameraOffsetX, -150, 150, 150);
        renderDesk();
        renderer::glRenderRect(r::texture_Noise, {(Uint8)dark,(Uint8)dark,(Uint8)dark,255}, projectMain.cameraOffsetX, -pos-size, 100, size);

        
        for (int i = 0; i < objects.size(); i++) {
            objects.at(i).render();
        }
        
        float blocksize = 20;
        renderer::glRenderRect({255,0,0,255}, posx, -60, blocksize, blocksize);
    }
    
    
    void renderDesk() {
        const int points = 6;
        
        float sizey = 100; //TODO
        SDL_Color color = { 40, 40, 40, 255 };
        
        GLfloat position[] = {
            projectMain.cameraOffsetX, (GLfloat) -sizey
        };
        
        GLfloat square[points * FLOATS_PER_POINT] = {
            0,   sizey,  // Top left
            100, sizey,  // Top right
            100, 0,      // Bottom right
            
            100, 0,  // Bottom right
            0,   0,  // Bottom left
            0,   sizey   // Top left
        };
        
        GLfloat colors[points * FLOATS_PER_COLOR] = {
            (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Top left
            (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Top right
            (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Bottom right
            
            (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Bottom right
            (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Bottom left
            (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255   // Top left
        };
        
        static float offset = 0;
        if (world::isMoving)
            offset += world::cameraSpeed * speedModifier / 100;
        
        GLfloat texturecoords[points * FLOATS_PER_TEX_COORD] = {
            0.0f+offset, 0.0f,  // Top left
            1.0f+offset, 0.0f,  // Top right
            1.0f+offset, 1.0f,  // Bottom right
            
            1.0f+offset, 1.0f,  // Bottom right
            0.0f+offset, 1.0f,  // Bottom left
            0.0f+offset, 0.0f   // Top left
        };
        
        GLfloat barycentric[points * FLOATS_PER_BARYCENTRIC] = {
            1.0f, 0.0f, 0.0f,  // Top left
            0.0f, 1.0f, 0.0f,  // Top right
            0.0f, 0.0f, 1.0f,  // Bottom right
            
            1.0f, 0.0f, 0.0f,  // Bottom right
            0.0f, 1.0f, 0.0f,  // Bottom left
            0.0f, 0.0f, 1.0f   // Top left
        };
        
        GLfloat rotationPoint[] = {
            0, 0
        };
        
        glUniform2fv(renderer::glUniform_shapePos, 1, position);
        glUniform1f(renderer::glUniform_shapeRotation, 0.0f);
        glUniform2fv(renderer::glUniform_shapeRotationPoint, 1, rotationPoint);
        renderer::glRenderArrays(points, square, colors, texturecoords, barycentric, r::texture_Noise);
    }
    
}




