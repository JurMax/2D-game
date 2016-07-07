//
//  inputhandler.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef inputhandler_hpp
#define inputhandler_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

#include "projectmain.hpp"


bool isKeyDown(SDL_Scancode code);
bool isKeyPressed(SDL_Scancode code);


namespace inputHandler {
    void handleEvents();

    void addKey(SDL_KeyboardEvent key);
    void removeKey(SDL_KeyboardEvent key);
}

#endif /* inputhandler_hpp */
