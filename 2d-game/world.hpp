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

#import "baseobjects.hpp"
#import "player.hpp"
#import "projectmain.hpp"


extern std::vector<BaseObject> rectangles;
extern Player player;

namespace world {
    void create();

    void update();
    void render();
}


#endif /* world_hpp */
