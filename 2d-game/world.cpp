//
//  world.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 16-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "world.hpp"

#include "projectmain.hpp"
#include "inputhandler.hpp"

std::vector<BaseObject> rectangles;
Player player;


void world::create() {
    player = createPlayer();
}


void world::update() {
    /*if (isKeyDown(SDL_SCANCODE_F)) {
        xding += 2 * M_PI * secondsPassed;
    }
    double offsetx = sin(xding)*200; */
    
    if (isKeyPressed(SDL_SCANCODE_Q)) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        rectangles.push_back(createBaseObject((float) x - 50, (float) y - 50, 100, 100));
    }
    
    if (isKeyPressed(SDL_SCANCODE_BACKSPACE)) {
        if(rectangles.size() > 0)
            rectangles.pop_back();
    }
    
    player.update();
}


void world::render() {
    ProjectMain *project = ProjectMain::getInstance();
    for (unsigned i = 0; i < rectangles.size(); i++) {
        rectangles.at(i).render(project->renderer);
    }
    
    player.render();
}