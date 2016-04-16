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

class Player: public BaseObject {
public:
    void update();
    void render();
    
private:
    void handleInput();
    void resolveHitboxes();
};

Player createPlayer();

#endif /* player_hpp */
