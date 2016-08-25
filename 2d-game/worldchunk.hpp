//
//  worldchunk.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 27-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef worldchunk_hpp
#define worldchunk_hpp

#include <stdio.h>

#include "projectmain.hpp"

using namespace std;

extern int collectiveChunkSize;

class WorldChunk {
public:
    int id;
    int posX;
    int width;
    int place;
    
    vector<BaseObject> chunkobjects;
    int listStart;
    int listEnd;
    
    bool isOnScreen();
    void removeObjectFromList();
    void placeObjectInList();
    
    int calculateSize();
};

void addNewChunk();
WorldChunk randomChunk();

namespace c {
    WorldChunk chunkEmpty();
    WorldChunk chunkTunnel();
    WorldChunk chunkObstacel();
}

#endif /* worldchunk_hpp */



