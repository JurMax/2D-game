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
        objects.push_back(chunkobjects.at(i));
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
    c.id = (int) chunks.size();
    
    SDL_Color debugColor = { static_cast<Uint8>(rand() * 255), static_cast<Uint8>(rand() * 255), static_cast<Uint8>(rand() * 255), 255 };
    
    for (unsigned i = 0; i < c.chunkobjects.size(); i++) {
        BaseObject obj = c.chunkobjects.at(i);
        obj.chunkID = c.id;
        obj.posX += c.posX;
        obj.debugColor = debugColor;
        
        objects.push_back(obj);
    }
    
    chunks.push_back(c);
}



WorldChunk randomChunk() {
    WorldChunk chunk = c::chunkOne();
    //TODO: generate random chunk
    
    chunk.posX = collectiveChunkSize;
    collectiveChunkSize += chunk.calculateSize();
    
    return chunk;
}




WorldChunk c::chunkOne() {
    WorldChunk c;
    for (int i = 0; i < 5; i++) {
        BaseObject obj = createBaseObject((float) 100 * i, 0, 100, 100);
        c.chunkobjects.push_back(obj);
    }
    return c;
}



