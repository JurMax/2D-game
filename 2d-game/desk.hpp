//
//  desk.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 21-08-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef desk_hpp
#define desk_hpp

#include <stdio.h>

#include "projectmain.hpp"
#include "world.hpp"


namespace desk {
    
    extern vector<BaseObject> objects;
    
    void create();
    
    void update();
    void render();
    
    void renderDesk();
}

#endif /* desk_hpp */
