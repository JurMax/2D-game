//
//  world.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 16-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef world_hpp
#define world_hpp

#include <stdio.h>
#include <vector>
#include <math.h>

#include "projectmain.hpp"
#include "player.hpp"
#include "baseobjects.hpp"
#include "worldchunk.hpp"

using namespace std;


namespace world {
    
    extern vector<WorldChunk> chunks;
    extern vector<BaseObject> objects;
    
    extern Player player;
    
    extern bool isMoving;
    extern float cameraSpeed;
    
    
    void create();

    void update();
    void render();
    
    void debug();
}


#endif /* world_hpp */



