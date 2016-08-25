//
//  worldchunk.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 27-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "worldchunk.hpp"

#include "world.hpp"

int collectiveChunkSize = 0;


bool WorldChunk::isOnScreen() {
    return true;
}


void WorldChunk::removeObjectFromList() {
    
}


void WorldChunk::placeObjectInList() {
    for (unsigned i = 0; i < chunkobjects.size(); i++) {
        world::objects.push_back(chunkobjects.at(i));
    }
}


int WorldChunk::calculateSize() {
    bool defined = false;
    float smallestX = 0.0;
    float largestX = 0.0;
    for (unsigned i = 0; i < chunkobjects.size(); i++) {
        BaseObject obj = chunkobjects.at(i);
        if (!defined) {
            defined = true;
            smallestX = obj.posX;
            largestX = obj.posX + obj.width;
        } else {
            if (obj.posX < smallestX) {
                smallestX = obj.posX;
            }
            if (obj.posX + obj.width > largestX) {
                largestX = obj.posX + obj.width;
            }
        }
    }
    
    width = largestX - smallestX;
    return width;
}



void addNewChunk() {
    WorldChunk c = randomChunk();
    c.posX = collectiveChunkSize;
    collectiveChunkSize += c.calculateSize();

    c.id = (int) world::chunks.size();
    
    for (unsigned i = 0; i < c.chunkobjects.size(); i++) {
        BaseObject obj = c.chunkobjects.at(i);
        obj.chunkID = c.id;
        obj.posX += c.posX;
        
        world::objects.push_back(obj);
    }
    
    world::chunks.push_back(c);
}


WorldChunk randomChunk() {
    int chunkAmount = 3;
    int r = rand() / (float) RAND_MAX * chunkAmount;
    
    if (r == 0) return c::chunkEmpty();
    if (r == 1) return c::chunkTunnel();
    if (r == 2) return c::chunkObstacel();
    
    else {
        printError("no chunk generated!");
        return c::chunkEmpty();
    }
}



WorldChunk c::chunkEmpty() {
    WorldChunk c;
    SDL_Color randomColor = { (Uint8) (rand() * 255), (Uint8) (rand() * 255), (Uint8) (rand() * 255), 255 };
    for (int i = 0; i < 5; i++) {
        if (i != 2 && i != 3) {
            BaseObject obj = createBaseObject((float) 20 * i, 0, 20, 20);
            obj.debugColor = randomColor;
            c.chunkobjects.push_back(obj);
        }
    }
    return c;
}

WorldChunk c::chunkTunnel() {
    WorldChunk c;
    SDL_Color randomColor = { (Uint8) (rand() * 255), (Uint8) (rand() * 255), (Uint8) (rand() * 255), 255 };
    SDL_Color randomColor2 = { (Uint8) (rand() * 255), (Uint8) (rand() * 255), (Uint8) (rand() * 255), 255 };
    for (int i = 0; i < 5; i++) {
        BaseObject obj = createBaseObject((float) 20 * i, 0, 20, 20);
        obj.debugColor = randomColor;
        c.chunkobjects.push_back(obj);
        
        
        BaseObject obj2 = createBaseObject((float) 20 * i, 60, 20, 20);
        obj2.debugColor = randomColor2;
        c.chunkobjects.push_back(obj2);
    }
    BaseObject obj = createBaseObject((float) 20 * 2, 40, 20, 20);
    obj.debugColor = randomColor2;
    c.chunkobjects.push_back(obj);
    
    return c;
}

WorldChunk c::chunkObstacel() {
    WorldChunk c;
    SDL_Color randomColor = { (Uint8) (rand() * 255), (Uint8) (rand() * 255), (Uint8) (rand() * 255), 255 };
    for (int i = 0; i < 4; i++) {
        BaseObject obj = createBaseObject((float) 20 * i, 0, 20, 20);
        obj.debugColor = randomColor;
        c.chunkobjects.push_back(obj);
    }
    BaseObject obj = createBaseObject((float) 50, 20, 20, 20);
    obj.debugColor = { 255, 0, 0, 255 };
    c.chunkobjects.push_back(obj);
    
    return c;
}


