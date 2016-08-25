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

bool isTyping = false;
string line = "";
float lineFloat = 0;

const int typingDashTime = 40;
int nextTypingDash = typingDashTime;
bool typingDash = true;


bool isKeyDown(SDL_Scancode code) {
    bool isDown = false;
    if (!isTyping) {
        for (int i = 0; i < itemsInKeysDown; i++) {
            if (keysDown[i] == code) {
                isDown = true;
                break;
            }
        }
    }
    return isDown;
}


bool isKeyPressed(SDL_Scancode code) {
    bool isPressed = false;
    if (!isTyping) {
        for (int i = 0; i < itemsInKeysDown; i++) {
            if (keysDown[i] == code && keysPressed[i]) {
                isPressed = true;
                break;
            }
        }
    }
    return isPressed;
}


float inputHandler::getLastInputedNumber() {
    lineFloat = ::atof(line.c_str());
    cout << lineFloat << endl;
    return lineFloat;
}


string inputHandler::getLine() {
    string str = line;
    
    if (typingDash && isTyping) {
        str += "_";
    }
    
    return str;
}



void inputHandler::handleEvents() {
    
    /* set all keysPressed to false */
    if (itemsInKeysDown > 0) {
        for (int i = 0; i < itemsInKeysDown; i++) {
            keysPressed[i] = false;
        }
    }
    
    SDL_Event e;
    while(SDL_PollEvent( &e )) {
        if (e.type == SDL_QUIT) {
            projectMain.gameRunning = false;
            break;
        }
          if (e.type == SDL_KEYDOWN) {
            inputHandler::addKey(e.key);
        }
        if (e.type == SDL_KEYUP) {
            inputHandler::removeKey(e.key);
        }
    }
    
    handleTypingInput();
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



void inputHandler::handleTypingInput() {
    
    if (isKeyPressed(SDL_SCANCODE_RETURN)) {
        isTyping = true;
        
        nextTypingDash = typingDashTime;
        typingDash = true;
    }
    
    else if (isTyping) {
        bool isShiftDown = false;
        for (int i = 0; i < itemsInKeysDown; i++) {
            SDL_Scancode k = keysDown[i];
            if (k == SDL_SCANCODE_LSHIFT || k == SDL_SCANCODE_RSHIFT) {
                isShiftDown = true;
            }
        }
        
        for (int i = 0; i < itemsInKeysDown; i++) {
            SDL_Scancode k = keysDown[i];
            
            if (keysPressed[i]) {
                if (k == SDL_SCANCODE_RETURN || k == SDL_SCANCODE_ESCAPE) {
                    isTyping = false;
                }
                else {
                    if (k == SDL_SCANCODE_SPACE) {
                        line += " ";
                    }
                    else if (k == SDL_SCANCODE_BACKSPACE) {
                        if (!isShiftDown) {
                            line = line.substr(0, line.size() - 1);
                        }
                        else {
                            line = "";
                        }
                    }
                    else {
                        char c = getChar(keysDown[i], isShiftDown);
                        if (c != 0) {
                            line += c;
                        }
                    }
                }
            }
        }
        
        nextTypingDash--;
        if (nextTypingDash < 0) {
            nextTypingDash = typingDashTime;
            typingDash = !typingDash;
        }
    }
}


char inputHandler::getChar(SDL_Scancode scancode, bool shiftdown) {
    const char *str = SDL_GetScancodeName(scancode);
    if (strlen(str) != 1) {
        return 0;
    }
    
    char c = str[0];
    
    if (shiftdown) {
        if (c == '1') c = '!';
        if (c == '2') c = '@';
        if (c == '3') c = '#';
        if (c == '4') c = '$';
        if (c == '5') c = '%';
        if (c == '6') c = '^';
        if (c == '7') c = '&';
        if (c == '8') c = '*';
        if (c == '9') c = '(';
        if (c == '0') c = ')';
        
        if (c == '-') c = '_';
        if (c == '=') c = '+';
        if (c == '[') c = '{';
        if (c == ']') c = '}';
        if (c == ';') c = ':';
        if (c == '\'') c = '"';
        if (c == '\\') c = '|';
        if (c == ',') c = '<';
        if (c == '.') c = '>';
        if (c == '/') c = '?';
        if (c == '`') c = '~';
    }
    else {
        //c = tolower(c);
    }
    
    return c;
}


