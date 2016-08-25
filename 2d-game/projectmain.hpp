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
#include <vector>
#include <math.h>

#define GL3_PROTOTYPES 1
#ifdef __APPLE__
    #include <SDL2/SDL.h>
    #include <SDL2_image/SDL_image.h>
    #include <SDL2_ttf/SDL_ttf.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
#endif
#include <glew.h>

#include "functions.hpp"
#include "renderer.hpp"
#include "inputhandler.hpp"
#include "baseobjects.hpp"
#include "resources.hpp"

#include "jtypes.hpp"
#include "debughandler.hpp"


class ProjectMain {
public:
    bool gameRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext glContext;
    
    GLuint glProgram;
    GLuint vertexShader, fragmentShader;
    
    int currentFPS = 0;
    float framerateModifier = 1;
    int glTriangleCount = 0;
    
    float cameraOffsetX = 0;
    float cameraOffsetY = 0;
    float debugCameraOffsetX = 0;
    float debugCameraOffsetY = 0;
    
private:
    int prefTime = 0;
    int framesCounter = 0;

    
public:
    void setup();
    void loadResources();
    float getSecondsRunning();
    

private:
    bool initializeSDL();
    bool initializeGL();
    
    void runGame();
    void updateLoop();
    void renderLoop();
    
    void printglProgramLog();
};


extern ProjectMain projectMain;
void start();

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 700;
const char WINDOW_NAME[] = "Ye'r Stinky";

#endif /* projectmain_hpp */

