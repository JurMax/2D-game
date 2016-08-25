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

using namespace std;

bool isKeyDown(SDL_Scancode code);
bool isKeyPressed(SDL_Scancode code);


namespace inputHandler {
    
    float getLastInputedNumber();
    string getLine();

    void handleEvents();

    
    void addKey(SDL_KeyboardEvent key);
    void removeKey(SDL_KeyboardEvent key);
    
    void handleTypingInput();
    char getChar(SDL_Scancode scancode, bool shiftdown);
}

#endif /* inputhandler_hpp */
