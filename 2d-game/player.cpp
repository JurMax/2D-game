//
//  player.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 16-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "player.hpp"

#include "inputhandler.hpp"
#include "world.hpp"

using namespace std;

Player createPlayer() {
    Player p;
    p.posX = 0;
    p.posY = 0;
    
    p.width = 50;
    p.height = 50;
    
    return p;
}


void Player::update() {
    ProjectMain *project = ProjectMain::getInstance();
    float speed = 500;
    
    if (onGround) {
        if (isKeyDown(SDL_SCANCODE_SPACE)){
            velocityY = -1500;
        }
    }
    if (isKeyDown(SDL_SCANCODE_A)){
        velocityX = -speed;
    }
    if (isKeyDown(SDL_SCANCODE_D)){
        velocityX = speed;
    }
    
    
    velocityX *= 0.7;
    
    velocityY += 50;
    
    posY += velocityY * project->secondsPassed;
    posX += velocityX * project->secondsPassed;
    
    
    resolveHitboxes();
    
    if (onGround) {
        velocityY = 0;
    }
}


void Player::render() {
    ProjectMain *project = ProjectMain::getInstance();

    SDL_Rect rect;
    rect.x = posX;
    rect.y = posY;
    rect.w = width;
    rect.h = height;
    
    SDL_SetRenderDrawColor(project->renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(project->renderer, &rect);
}


void Player::handleInput() {
    
}


void Player::resolveHitboxes() {
    
    bool collided = false;
    
    int w, h;
    SDL_GetWindowSize(ProjectMain::getInstance()->window, &w, &h);
    if (posY > h - height - 50) {
        posY = h - height - 50;
        collided = true;
    }

    for (unsigned i = 0; i < rectangles.size(); i++) {
        BaseObject rect = rectangles.at(i);
        
        bool sameX = posX + width > rect.posX && posX < rect.posX + rect.width;
        bool sameY = posY + height > rect.posY && posY < rect.posY + rect.height;
        if (sameX && sameY) {
            posY = rect.posY - height;
            collided = true;
        }
    }
    
    if (collided) {
        onGround = true;
        velocityY = 0;
    } else {
        onGround = false;
    }
}





