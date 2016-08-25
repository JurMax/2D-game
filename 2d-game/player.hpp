//
//  player.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 16-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include "baseobjects.hpp"
#include "inputhandler.hpp"

class Player: public BaseObject {
public:
    bool isDead = false;
    
    float leftArmPosX = 0, leftArmPosY = 0;
    float rightArmPosX = 0, rightArmPosY = 0;
    float leftLegPosX = 0, leftLegPosY = 0;
    float rightLegPosX = 0, rightLegPosY = 0;
    float headPosX = 0, headPosY = 0;
    float rightEarRotation = 45;
    float leftEarRotation = 45;
    
    float volume;
    bool isPlayer2;
    SDL_Scancode left, right, jump, heightup, heightdown, shrink, grow;
    
    void setPlayer2();
    void update();
    void render();
    
    void setDead();
    void respawn();
    
private:
    bool facingLeft = false;
    
    void renderPlayer();
    void resolveHitboxes();
    bool handleObjectHitbox(BaseObject rect, float timePassed);
};

Player createPlayer();

#endif /* player_hpp */
