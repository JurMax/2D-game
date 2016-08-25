//
//  baseswitch.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 28-07-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef baseswitch_hpp
#define baseswitch_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

#include "projectmain.hpp"

class BaseSwitch;

class BaseSwitch {
public:
    float posX, posY;
    float width, height;
    
    BaseObject *boundObject;
    BaseObject *boundSwitch;
    
    void update();
    void render();
    
    void onActived();
};


class BasicSwitch : public BaseSwitch {
    float width = 20;
    float height = 20;
};


BasicSwitch newSwitch(float posx, float posy, BaseObject *boundobject);
#endif /* baseswitch_hpp */
