//
//  world.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 16-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "world.hpp"

vector<WorldChunk> chunks;
vector<BaseObject> objects;

Player player;
Player player2;


void world::create() {
    player = createPlayer();
    player2 = createPlayer();
    player2.setPlayer2();
    
    /*for (int i = 0; i < 20; i++) {
        BaseObject newobj = createBaseObject((float) 100 * i - 500, 0, 100, 100);
        newobj.debugColor = { static_cast<Uint8>(rand() * 255), static_cast<Uint8>(rand() * 255), static_cast<Uint8>(rand() * 255) };
        objects.push_back(newobj);
    } */
    
    addNewChunk();
    addNewChunk();
    addNewChunk();
}

float scaleX = 1, scaleY = 1;
void world::update() {
    
    if (isKeyDown(SDL_SCANCODE_Q)) {
        //projectMain.secondsPassed *= 0.5;
        scaleY = scaleX += 0.05;
        SDL_RenderSetScale(projectMain.renderer, scaleX, scaleY);
    } else if (isKeyDown(SDL_SCANCODE_E)) {
        scaleY = scaleX -= 0.05;
        SDL_RenderSetScale(projectMain.renderer, scaleX, scaleY);
    }
    
    debug();
    
    
    /*  chunk stuff  */
    for (unsigned i = 0; i < chunks.size(); i++) {
        if (!chunks.at(i).isOnScreen()) {
            chunks.at(i).removeObjectFromList();
        }
    }
    
    bool createNewChunk = true;
    for (unsigned i = 0; i < objects.size(); i++) {
        BaseObject obj = objects.at(i);
        
        obj.update();
        
        /* if there is a rectangle still outside the screen, then there is no need for a new chunk */
        if (obj.posX > SCREEN_WIDTH - projectMain.screenOffsetX) {
            createNewChunk = false;
        }
        
        if (obj.posX + obj.width < -projectMain.screenOffsetX) {
            //objects.erase(objects.begin() + i);
        }
    }
    if (createNewChunk) {
        addNewChunk();
    }
    
    
    player.update();
    //player2.update();
    
    
    if (!STATIC_SCREEN) {  /* set screen position */
        projectMain.screenOffsetX = -player.posX - player.width/2;
        projectMain.screenOffsetY = -player.posY - player.height/2;
    }
}



float angle = 0;
void world::render() {
    angle += 100 * projectMain.secondsPassed;
    SDL_Rect b;
    b.x = projectMain.screenOffsetX/10 + 1000;
    b.y = projectMain.screenOffsetY/100;
    b.w = SCREEN_WIDTH; b.h = SCREEN_HEIGHT;
    //renderer::renderTexture(r::circle, NULL, &b, angle, NULL);
    
    for (unsigned i = 0; i < objects.size(); i++) {
        objects.at(i).render();
    }
    
    player.render();

    //player2.render();
}



void world::debug() {
    int x = getMouseX() / 100;
    int y = getMouseY() / 100;
    
    
    /* debug object placement */
    if (isKeyPressed(SDL_SCANCODE_RSHIFT))
        objects.push_back(createBaseObject((float) getMouseX() - 50, (float) getMouseY() - 50, 100, 100));
    if (isKeyDown(SDL_SCANCODE_RETURN)) {
        
        bool alreadyPlaced = false;
        for (int i = 0; i < objects.size(); i++) {
            BaseObject rect = objects.at(i);
            if (rect.posX == x * 100 && rect.posY == y * 100) {
                alreadyPlaced = true;
                break;
            }
        }
        if (!alreadyPlaced) {
            BaseObject newobj = createBaseObject((float) x * 100, (float) y * 100, 100, 100);
            newobj.debugColor = { static_cast<Uint8>(rand() * 255), static_cast<Uint8>(rand() * 255), static_cast<Uint8>(rand() * 255), 255 };
            objects.push_back(newobj);
        }
    }
    
    if (isKeyDown(SDL_SCANCODE_BACKSPACE)) {
        if (isKeyDown(SDL_SCANCODE_RSHIFT)) {
            if(objects.size() > 0)
                objects.pop_back();
        } else {
            for (int i = 0; i < objects.size(); i++) {
                BaseObject rect = objects.at(i);
                if (rect.posX == x * 100 && rect.posY == y * 100) {
                    objects.erase(objects.begin() + i);
                    break;
                }
            }
        }
    }
    
    
    
    if (isKeyPressed(SDL_SCANCODE_E)) {
        for (int i = 0; i < objects.size(); i++) {
            BaseObject rect = objects.at(i);
            if (rect.posX == x * 100 && rect.posY == y * 100) {
                objects.at(objects.size()-1).isMoving = true;
                break;
            }
        }
    }
}



