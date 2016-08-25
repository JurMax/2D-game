//
//  resources.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 28-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "resources.hpp"

namespace r {
    
    bool loadingSuccesful = true;
    
    SDL_Window *gWindow;
    SDL_Renderer *gRenderer;
    
    TTF_Font *ttf_sans;
    SDL_Texture *circle;
    SDL_Texture *tblank;
    
    GLuint texture_Blank = -1;
    GLuint texture_Circle = -1;
    GLuint texture_Debug = -1;
    GLuint texture_Font = -1;
    GLuint texture_Noise = -1;


    bool loadResources() {
        string str = "";
        str.append(SDL_GetBasePath());
        str += "resources/plasmati.ttf";
        ttf_sans = TTF_OpenFont(str.c_str(), 50);
    
        //circle = loadTexture("circle.png");
        //tblank = loadTexture("blank.png");
        
        gWindow = NULL;
        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        
        texture_Blank = loadGLTexture("blank.png");
        texture_Circle = loadGLTexture("circle.png");
        texture_Debug = loadGLTexture("debug.png");
        texture_Font = loadGLTexture("pixelfont.png");
        texture_Noise = loadGLTexture("noise.png");

        
        return loadingSuccesful;
    }
    
    
    void destroyResources() {
        TTF_CloseFont(ttf_sans);
        SDL_DestroyTexture(circle);
        SDL_DestroyTexture(tblank);
        
        glDeleteTextures(1, &texture_Blank);
        glDeleteTextures(1, &texture_Circle);
        glDeleteTextures(1, &texture_Debug);
    }


    GLuint loadGLTexture(string file) {
        string path = "";
        path.append(SDL_GetBasePath());
        path += "resources/";
        
        SDL_Surface* loadingSurface = IMG_Load((path + file).c_str());
        if (loadingSurface == NULL) {
            printf("Unable to load image %s to surface! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            loadingSuccesful = false;
            return NULL;
        }
        
        
        GLuint texture = -1;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, loadingSurface->w, loadingSurface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, loadingSurface->pixels);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        SDL_FreeSurface(loadingSurface);
        
        return texture;
    }
    
    SDL_Texture* loadTexture(std::string file) {
        string path = "";
        path.append(SDL_GetBasePath());
        path += "resources/";
        
        SDL_Texture *texture;
        SDL_Surface* loadingSurface = IMG_Load((path + file).c_str());
        if (loadingSurface == NULL) {
            printf("Unable to load image %s to surface! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
            loadingSuccesful = false;
            return NULL;
        }
        else {

            texture = SDL_CreateTextureFromSurface(gRenderer, loadingSurface);
            if (texture == NULL) {
                printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
            }
            
            //Get rid of old loaded surface
            SDL_FreeSurface(loadingSurface);
        }
        
        return texture;
    }
}



