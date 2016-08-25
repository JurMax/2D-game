//
//  baseswitch.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 28-07-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "baseswitch.hpp"


BasicSwitch newSwitch(float posx, float posy, BaseObject *boundobject) {
    BasicSwitch newswitch;
    newswitch.posX = posx;
    newswitch.posY = posy;
    newswitch.boundObject = boundobject;
    
    return newswitch;
}