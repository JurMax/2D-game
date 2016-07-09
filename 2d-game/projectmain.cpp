//
//  projectmain.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 09-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "projectmain.hpp"

#include "world.hpp"

using namespace std;


ProjectMain projectMain;

void start() {
    projectMain.setup();
}


///////// projectMain /////////

void ProjectMain::setup() {
    
    if (!initializeSDL()) {
        printError("Failed to create SDL environment!");
    }
    else {
        if (!initializeGL()) {
            printError("Failed to create openGL environment!");
        }
        else {
            if (!r::loadResources()) {
                printError("Failed to load one or multiple resources!");
            }
            else {
                if (!renderer::initializeRenderer()) {
                    printError("Failed to read shader attribute locations!");
                }
                else {
                    runGame();
                }
            }
        }
    }
    
    r::destroyResources();
    renderer::cleanup();
    SDL_DestroyRenderer(renderer);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


bool ProjectMain::initializeSDL() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string error = "Failed to initialize SDL! SDL_Error: ";
        error.append(SDL_GetError());
        printError(error);
    }
    else {
        if (TTF_Init() < 0) {
            std::string error = "Failed to initialize SDL_TTF! TTF_Error: ";
            error.append(TTF_GetError());
            printError(error);
        }
        else {
            if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                std::string error = "Failed to initialize SDL_image! IMG_Error: ";
                error.append(IMG_GetError());
                printError(error);
            }
            else {
                window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

                if (window == NULL) {
                    std::string error = "Failed to create SDL_Window! SDL_Error: ";
                    error.append(SDL_GetError());
                    printError(error);
                }
                else {
                    return true;
                }
            }
        }
    }
    
    return false;
}


bool ProjectMain::initializeGL() {
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetSwapInterval(1); //Enables v-sync
    
    
    glContext = SDL_GL_CreateContext(window);
    
    if (glContext == NULL) {
        printError("Failed to create GL context!");
    }
    else {
        glewExperimental = GL_TRUE;
        GLenum glew = glewInit();
        if (glew != GLEW_OK) {
            printError("Failed to initialise GLEW!");
            return false;
        }
        else {
            glProgram = glCreateProgram();
            
            loadShader(GL_VERTEX_SHADER);
            loadShader(GL_FRAGMENT_SHADER);
            
            glLinkProgram(glProgram);
            
            GLint programLinked = GL_TRUE;
            glGetProgramiv(glProgram, GL_LINK_STATUS, &programLinked);
            if (programLinked != GL_TRUE) {
                printError("Failed to link program!");
                
                std::cout << "=======================================\n";
                int maxLength; glGetProgramiv(glProgram, GL_INFO_LOG_LENGTH, &maxLength);
                char* shaderProgramInfoLog = new char[maxLength];
                glGetProgramInfoLog(glProgram, maxLength, &maxLength, shaderProgramInfoLog);
                
                std::cout << "Linker error message: " << shaderProgramInfoLog << std::endl;
                delete[] shaderProgramInfoLog;
            }
            else {
                glEnable(GL_BLEND);
                //glBlendEquation(GL_FUNC_ADD);
                glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
                
                
                return true;
            }
        }
    }
    
    return false;
}



void ProjectMain::runGame() {
    timeRunning = time(0);
    prefTime = getSecondsRunning();
    previousTicks = SDL_GetTicks();
    
    
    if (!SHOW_MOUSE)
        SDL_ShowCursor(SDL_DISABLE);

    world::create();
    
    gameRunning = true;
    while (gameRunning) {
        updateLoop();
        renderLoop();
    }
}


void ProjectMain::updateLoop() {
    
    /* how many seconds have passed (for unlocked framerates) */
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
    
    if (isKeyPressed(SDL_SCANCODE_M)) {
        SDL_ShowCursor(SDL_ENABLE);
    }
    
    world::update();
    
    if (isKeyDown(SDL_SCANCODE_ESCAPE)) {
        gameRunning = false;
    }
}


void ProjectMain::renderLoop() {
    glUseProgram(glProgram);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    renderer::setUniforms();

    world::render();
    
    
    // Render FPS //
    /*if (r::ttf_sans != NULL) {
        char buffer[16];
        sprintf(buffer, "FPS: %i", currentFPS);
        render::renderText(r::ttf_sans, buffer, 0, 0, { 255, 255, 255, 255 });
    }*/
    
    if (!SHOW_MOUSE || true) {
        float x = getMouseX();
        float y = getMouseY();
        
        float size = 40;
        renderer::glRenderRect({ 0, 0, 0, 150 }, x - size/2, y - size/2, size, size);
        renderer::glRenderRect({ 255, 255, 255, 150 }, x - (size-2)/2, y - (size-2)/2, size-2, size-2);
    }
    
    if (isKeyPressed(SDL_SCANCODE_1)) {
        float r = (float) rand() / (float) RAND_MAX;
        float g = (float) rand() / (float) RAND_MAX;
        float b = (float) rand() / (float) RAND_MAX;
        glClearColor(r, g, b, 1.0);
    }
    
    SDL_GL_SwapWindow(window);
    
    
    static char buffer[64];
    sprintf(buffer, "SDL Game Window | JurMax  |  Triangles: %i | FPS: %i", glTriangleCount, currentFPS);
    SDL_SetWindowTitle(window, buffer);
    glTriangleCount = 0;
    
    GLenum err;
    while ( ( err = glGetError() ) != GL_NO_ERROR) {
        std::cerr << "GL_ERROR: " << err << endl;
    }
}



float ProjectMain::getSecondsRunning() {
    float ticks = SDL_GetTicks();
    return ticks / 1000;
}



