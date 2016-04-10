//
//  projectmain.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 09-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef projectmain_hpp
#define projectmain_hpp

#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "inputhandler.hpp"
#include "functions.hpp"


class ProjectMain {
public:
    bool gameRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *ttf_sans;
    
    float secondsPassed;
    int currentFPS = 0;
    
private:
    int previousTicks = 0;
    time_t timeRunning;  /* for fps calculation */
    int prefTime = 0;
    int framesCounter = 0;
    
    
public:
    void setup();
    void loadResources();
    float getSecondsRunning();

private:
    bool initializeSDL();

    void updateLoop();
    void renderLoop();
};



class TestClass {
public:
    void setChar(char c);
    void printChar();
private:
    char ch;
};


const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const char WINDOW_NAME[] = "Ye'r Stinky";


static ProjectMain projectMain;

namespace projectmain {
    void start();
}


#endif /* projectmain_hpp */

