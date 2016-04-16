//
//  inputhandler.cpp
//  2d - game
//
//  Created by Jurriaan van den Berg on 11-02-16.
//  Copyright © 2016 Spasticom. All rights reserved.
//

#include "inputhandler.hpp"

SDL_Scancode keysDown[16];
bool keysPressed[16]; /* only active for one tick */

int itemsInKeysDown = 0;


/* public */
bool isKeyDown(SDL_Scancode code) {
    bool isDown = false;
    for (int i = 0; i < itemsInKeysDown; i++) {
        if (keysDown[i] == code) {
            isDown = true;
            break;
        }
    }
    return isDown;
}


bool isKeyPressed(SDL_Scancode code) {
    bool isPressed = false;
    for (int i = 0; i < itemsInKeysDown; i++) {
        if (keysDown[i] == code && keysPressed[i]) {
            isPressed = true;
            break;  
        }
    }
    return isPressed;
}



void inputHandler::handleEvents() {

    /* set all keysPressed to false */
    if (itemsInKeysDown > 0) {
        for (int i = 0; i < itemsInKeysDown; i++) {
            keysPressed[i] = false;
        }
    }
    
    SDL_Event e;
    while( SDL_PollEvent( &e ) ){
        if (e.type == SDL_QUIT) {
            ProjectMain *project = ProjectMain::getInstance();
            project->gameRunning = false;
            break;
        }
        if (e.type == SDL_KEYDOWN) {
            inputHandler::addKey(e.key);
        }
        if (e.type == SDL_KEYUP) {
            inputHandler::removeKey(e.key);
        }
    }
    
}


void inputHandler::addKey(SDL_KeyboardEvent key) {
    if (itemsInKeysDown < 15) {
        bool isAlreadyAdded = false;
        for (int i = 0; i < itemsInKeysDown; i++) {
            if (keysDown[i] == key.keysym.scancode) {
                isAlreadyAdded = true;
            }
        }
        if (isAlreadyAdded == false) {
            keysDown[itemsInKeysDown] = key.keysym.scancode;
            keysPressed[itemsInKeysDown] = true;
            itemsInKeysDown++;
        }
        
    }
    
}

void inputHandler::removeKey(SDL_KeyboardEvent key) {
    if (itemsInKeysDown > 0) {
        for (int i = 0; i < itemsInKeysDown; i++) {
            if (keysDown[i] == key.keysym.scancode) {
                for (int i2 = i; i2 < itemsInKeysDown - 1; i2++) {
                    keysDown[i2] = keysDown[i2+1];
                }
                itemsInKeysDown--;
            }
        }
    }
}
