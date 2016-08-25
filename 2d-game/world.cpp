//
//  world.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 16-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "world.hpp"


namespace world {
    
    vector<WorldChunk> chunks;
    vector<BaseObject> objects;
    
    Player player;
    
    bool isMoving = false;
    float cameraSpeed = 1;
    
    
    void create() {
        player = createPlayer();
    
        addNewChunk();
        addNewChunk();
        addNewChunk();
        
        debug::add(&cameraSpeed, "speed");
    }
    

    void update() {
    
        for (int i = 0; i < chunks.size(); i++) {
            if (!chunks.at(i).isOnScreen()) {
                chunks.at(i).removeObjectFromList();
            }
        }
    
        bool createNewChunk = true;
        for (int i = 0; i < objects.size(); i++) {
            BaseObject obj = objects.at(i);
        
            obj.update();
        
            // if there is a rectangle still outside the screen, then there is no need for a new chunk
            if (obj.posX > projectMain.cameraOffsetX + 100) {
                createNewChunk = false;
            }
        
            if (obj.posX + obj.width < projectMain.cameraOffsetX) {
                objects.erase(objects.begin() + i);
            }
        }
    
        if (createNewChunk) {
            addNewChunk();
        }
    
        
        if (isKeyPressed(SDL_SCANCODE_V))
            isMoving = !isMoving;
    
        if (isMoving) {
            projectMain.cameraOffsetX += cameraSpeed * projectMain.framerateModifier;
        }
        
        player.update();
        
        debug();
    }



    void render() {
        
        // screen background
        renderer::glRenderRect({ 240, 240, 240, 255 }, projectMain.cameraOffsetX, 0, 100, 80);

        player.render();
    
        for (int i = 0; i < objects.size(); i++) {
            objects.at(i).render();
        }
    
        
    }



    void debug() {
        int x = getMouseX() / 20;
        int y = getMouseY() / 20;
    
        /* debug object placement */
        if (isKeyPressed(SDL_SCANCODE_RSHIFT)) {
            objects.push_back(createBaseObject((float) getMouseX() - 50, (float) getMouseY() - 50, 20, 20));
        }
        if (isKeyDown(SDL_SCANCODE_BACKSLASH)) {
            bool alreadyPlaced = false;
            for (int i = 0; i < objects.size(); i++) {
                BaseObject rect = objects.at(i);
                if (rect.posX == x * 20 && rect.posY == y * 20) {
                    alreadyPlaced = true;
                    break;
                }
            }
            if (!alreadyPlaced) {
                BaseObject newobj = createBaseObject((float) x * 20, (float) y * 20, 20, 20);
                newobj.debugColor = { (Uint8) (rand() * 255), (Uint8) (rand() * 255), (Uint8) (rand() * 255), 255 };
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
                    if (rect.posX == x * 20 && rect.posY == y * 20) {
                        objects.erase(objects.begin() + i);
                        break;
                    }
                }
            }
        }
    
        float speed = 3 * projectMain.framerateModifier;
        if (isKeyDown(SDL_SCANCODE_C)) {
            if (isKeyDown(SDL_SCANCODE_RIGHT)) projectMain.debugCameraOffsetX += speed;
            if (isKeyDown(SDL_SCANCODE_LEFT))  projectMain.debugCameraOffsetX -= speed;
            if (isKeyDown(SDL_SCANCODE_UP))    projectMain.debugCameraOffsetY += speed;
            if (isKeyDown(SDL_SCANCODE_DOWN))  projectMain.debugCameraOffsetY -= speed;
        }
    }
    
}



