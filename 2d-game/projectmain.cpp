//
//  projectmain.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 09-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "projectmain.hpp"

using namespace std;


void projectmain::start() {
    projectMain.setup();
}


///////// projectMain /////////

void ProjectMain::setup() {
    TestClass class1;
    TestClass class2;
    class1.setChar('a');
    class2.setChar('b');
    
    class1.printChar();
    class2.printChar();

    
    bool sdlloaded = initializeSDL();
    
    if (sdlloaded) {
        loadResources();
        
        timeRunning = time(0);
        prefTime = getSecondsRunning();
        
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
    cout << SDL_GetBasePath() << endl;
}


float ProjectMain::getSecondsRunning() {
    double ticks = SDL_GetTicks();
    return ticks / 1000;
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


////// debug //////
int size = 100;
SDL_Rect rect;
float posX = 0, posY = 0;
double xding = 0;



void ProjectMain::updateLoop() {
    float milisecondsPassed = SDL_GetTicks() - previousTicks;
    secondsPassed = milisecondsPassed / 1000;
    previousTicks = SDL_GetTicks();
    
    handleEvents();
    
    /* fps */
    framesCounter += 1;
    if (getSecondsRunning() > prefTime) {
        prefTime += 1;
        currentFPS = framesCounter;
        framesCounter = 0;
    }
    
    if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
        gameRunning = false;
    }
    
    if (isKeyDown(SDL_SCANCODE_F)) {
        xding += 3.14*2*secondsPassed;
    }
    
    float speed = 500 * secondsPassed;
    if (isKeyDown(SDL_SCANCODE_W)){
        posY = posY - speed;}
    if (isKeyDown(SDL_SCANCODE_S)){
        posY = posY + speed;}
    if (isKeyDown(SDL_SCANCODE_A)){
        posX = posX - speed;}
    if (isKeyDown(SDL_SCANCODE_D)){
        posX = posX + speed;}
    
    int x = 0; int y = 0; SDL_GetMouseState(&x, &y);
    double offsetx = sin(xding)*200;
    rect.w = size; rect.h = size;
    rect.x = posX + offsetx - rect.w/2;
    rect.y = posY - rect.w/2;
}


void ProjectMain::renderLoop() {
    SDL_SetRenderDrawColor(renderer, 34, 34, 34, 255);
    SDL_RenderClear(renderer);
    
    
    /* render square */
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    
    /* Render FPS */
    if (ttf_sans != NULL) {
        char buffer[40];
        sprintf(buffer, "FPS: %i", currentFPS);
        SDL_Color color = {255, 255, 255};
        renderText(renderer, ttf_sans, buffer, 0, 0, color);
    }
    
    
    SDL_RenderPresent(renderer); //update screen
}

///////// end - projectMain /////////



void TestClass::setChar(char c) {
    ch = c;
}


void TestClass::printChar() {
    cout << ch << endl;
}



