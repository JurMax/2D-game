//
//  projectmain.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 09-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "projectmain.hpp"

#include "inputhandler.hpp"
#include "functions.hpp"
#include "baseobjects.hpp"
#include "world.hpp"

using namespace std;

ProjectMain ProjectMain::projectInstance;


///////// projectMain /////////

void ProjectMain::setup() {
    
    bool sdlloaded = initializeSDL();
    
    if (sdlloaded) {
        loadResources();
        
        timeRunning = time(0);
        prefTime = getSecondsRunning();
        
        world::create();
        
        gameRunning = true;
        while (gameRunning) {
            updateLoop();
            renderLoop();
        }
    } else {
        printf("Failed to create SDL environment!\n");
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



void ProjectMain::loadResources() {
    std::string str = "";
    str.append(SDL_GetBasePath());
    str += "plasmati.ttf";
    str.c_str();
    ttf_sans = TTF_OpenFont("/Users/jurriaanvandenberg/Documents/Programming/C++/2D game - SDL/2d-game/resources/plasmati.ttf", 50);
    cout << SDL_GetError() << endl;
}


bool ProjectMain::initializeSDL() {
    bool i = false;
    
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else if( TTF_Init() < 0 ) {
        printf( "TTF could not initialize! TTF_Error: %s\n", TTF_GetError() );
    }
    else {
        window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        
        if( window == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }  else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            i = true;
        }
    }
    
    return i;
}


float ProjectMain::getSecondsRunning() {
    double ticks = SDL_GetTicks();
    return ticks / 1000;
}



void ProjectMain::updateLoop() {
    
    /* how many seconds have passed (unlocked framerate) */
    float milisecondsPassed = SDL_GetTicks() - previousTicks;
    secondsPassed = milisecondsPassed / 1000;
    previousTicks = SDL_GetTicks();
    
    /* fps */
    framesCounter += 1;
    if (getSecondsRunning() > prefTime) {
        prefTime += 1;
        currentFPS = framesCounter;
        framesCounter = 0;
    }
    
    
    inputHandler::handleEvents();
    
    world::update();
        
    if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
        gameRunning = false;
    }
}


void ProjectMain::renderLoop() {
    SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
    SDL_RenderClear(renderer);
    
    
    world::render();
    
    
    /* Render FPS */
    if (ttf_sans != NULL) {
        char buffer[40];
        sprintf(buffer, "FPS: %i", currentFPS);
        SDL_Color color = {255, 255, 255};
        renderText(renderer, ttf_sans, buffer, 0, 0, color);
    }
    
    SDL_RenderPresent(renderer); //update screen
}
