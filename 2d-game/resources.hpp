//
//  resources.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 28-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef resources_hpp
#define resources_hpp

#include <stdio.h>
#include "projectmain.hpp"

using namespace std;

namespace r {
    extern bool loadingSuccesful;
    
    extern TTF_Font *ttf_sans;
    extern SDL_Texture *circle;
    extern SDL_Texture *tblank;
    
    extern GLuint texture_Blank;
    extern GLuint texture_Circle;
    extern GLuint texture_Debug;
    extern GLuint texture_Font;
    extern GLuint texture_Noise;

    
    bool loadResources();
    void destroyResources();
    
    GLuint loadGLTexture(string file);
    SDL_Texture* loadTexture(string file);
}

#endif /* resources_hpp */
