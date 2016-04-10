//
//  inputhandler.cpp
//  2d - game
//
//  Created by Jurriaan van den Berg on 11-02-16.
//  Copyright © 2016 Spasticom. All rights reserved.
//

#include "inputhandler.hpp"

SDL_Scancode keysDown[16];
int itemsInKeys = 0;


bool isKeyDown(SDL_Scancode code) {
    bool isPressed = false;
    for (int i = 0; i < itemsInKeys; i++) {
        if (keysDown[i] == code) {
            isPressed = true;
            break;
        }
    }
    return isPressed;
}


void addKey(SDL_KeyboardEvent key) {
    if (itemsInKeys < 16) {
        bool isAlreadyAdded = false;
        for (int i = 0; i < itemsInKeys; i++) {
            if (keysDown[i] == key.keysym.scancode) {
                isAlreadyAdded = true;
            }
        }
        if (isAlreadyAdded == false) {
            keysDown[itemsInKeys] = key.keysym.scancode;
            itemsInKeys += 1;
        }
    }
}

void removeKey(SDL_KeyboardEvent key) {
    if (itemsInKeys > 0) {
        for (int i = 0; i < itemsInKeys; i++) {
            if (keysDown[i] == key.keysym.scancode) {
                for (int i2 = i; i2 < itemsInKeys-1; i2++) {
                    keysDown[i2] = keysDown[i2+1];
                }
                itemsInKeys -= 1;
            }
        }
    }
}


void handleEvents() {
    SDL_Event e;
    while( SDL_PollEvent( &e )){
        if (e.type == SDL_QUIT) {
            projectMain.gameRunning = false;
            break;
        }
        if (e.type == SDL_KEYDOWN) {
            addKey(e.key);
        }
        if (e.type == SDL_KEYUP) {
            removeKey(e.key);
        }
    }
}
