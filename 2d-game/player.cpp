//
//  player.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 16-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "player.hpp"

#include "world.hpp"
#include "functions.hpp"
#include "resources.hpp"

using namespace std;


int gravity = 4000;


const int BLINK_TIME = 5;
int nextBlink = 200;
int blinkTime = 200;
bool isBlinking = false;;


Player createPlayer() {
    Player p;
    
    p.isDead = false;
    
    p.posX = 0;
    p.posY = 200;
    
    p.width = 50;  /* 1 pixel = 1 cm */
    p.height = 50;
    
    p.volume = p.width * p.height;
    
    p.isPlayer2 = false;
    
    p.left = SDL_SCANCODE_A;
    p.right = SDL_SCANCODE_D;
    p.jump = SDL_SCANCODE_W;
    p.heightdown = SDL_SCANCODE_Z;
    p.heightup = SDL_SCANCODE_X;
    p.shrink = SDL_SCANCODE_T;
    p.grow = SDL_SCANCODE_G;
    
    glGenBuffers(2, p.vbo);
    glGenVertexArrays(1, p.vao);

    return p;
}


void Player::setPlayer2() {
    isPlayer2 = true;
    
    left = SDL_SCANCODE_LEFT;
    right = SDL_SCANCODE_RIGHT;
    jump = SDL_SCANCODE_UP;
    heightdown = SDL_SCANCODE_K;
    heightup = SDL_SCANCODE_I;
    shrink = SDL_SCANCODE_L;
    grow = SDL_SCANCODE_O;
}


void Player::update() {

    if (!isDead) {
        blinkTime += 1;

        if (!isBlinking) {
            if (blinkTime > nextBlink) {
                if ((float) rand() / (float) RAND_MAX < 0.7f)
                    nextBlink = 100;
                else
                    nextBlink = 10;
                blinkTime = 0;
                isBlinking = true;
            }
        } else {
            if (blinkTime > BLINK_TIME) {
                isBlinking = false;
                blinkTime = 0;
                isBlinking = false;
            }
        }
        
        
    
        
        if (isKeyDown(left)) {
            velocityX = -speed;
            facingLeft = true;
        }
        
        else if (isKeyDown(right)) {
            velocityX = speed;
            facingLeft = false;
        } else {
            velocityX *= 0.8;
        }
        
        if (isKeyDown(jump) && onGround) {
            velocityY = 1500;
        }
        
        
        if (isKeyDown(heightup))
            height += 2;
        if (isKeyDown(heightdown))
            height -= 2;
        if (height < 5) height = 5;
        
        double factor = 1.03;
        if (isKeyDown(grow)) {
            height *= factor;
            volume *= factor*factor;
            leftEarRotation -= 3;
            rightEarRotation -= 3;
        }
        if (isKeyDown(shrink)) {
            height /= factor;
            volume /= factor*factor;
            leftEarRotation += 3;
            rightEarRotation += 3;
        }
        width = volume / height;
        
        
        static bool gravityEnabled;
        if (isKeyPressed(SDL_SCANCODE_SPACE)) {
            if (gravityEnabled) gravityEnabled = false;
            else gravityEnabled = true;
        }
        
        if (gravityEnabled) {
            velocityY -= gravity * projectMain.secondsPassed; /* gravity */
        } else {
            if (isKeyDown(SDL_SCANCODE_W))
                velocityY = speed;
            if (isKeyDown(SDL_SCANCODE_S))
                velocityY = -speed;
            velocityY *= 40 * projectMain.secondsPassed;
        }
        
        
    
        //velocityX *= 40 * projectMain.secondsPassed;
        
        
        if (fabs(velocityX) < 0.0001f)
            velocityX = 0;
        if (fabs(velocityY) < 0.0001f)
            velocityY = 0;
        
        
        posY += velocityY * projectMain.secondsPassed;
        posX += velocityX * projectMain.secondsPassed;
        
        resolveHitboxes();
        
    }
    else if (isDead) {
        if (isKeyPressed(SDL_SCANCODE_R)) {
            respawn();
        }
    }
}

void Player::render() {
    //BaseObject::updateBuffers();
    //BaseObject::render();
    renderPlayer();
}

void Player::renderPlayer() {
    if (!isDead) {
        SDL_Color skinColor = { 0xFF, 255, 255, 255 };
        SDL_Color secondaryColor = { 200, 200, 200, 255 };
        
        const float EAR_OFFSET_Y = 12;
        float EAR_DISTANCE = 12;
        const float EAR_WIDTH = 20;
        const float EAR_HEIGHT = 50;
        
        float earPosX = posX + width/2 - EAR_WIDTH/2;
        if (facingLeft) {
            earPosX += 4;
            EAR_DISTANCE *= -1;
            
            leftEarRotation *= -1;
            rightEarRotation *= -1;
        }
        else {
            earPosX -= 4;
        }
        
        
        /* left (back) ear */
        renderer::glRenderCircle(secondaryColor, earPosX + EAR_DISTANCE/2, posY + height - EAR_OFFSET_Y, EAR_WIDTH, EAR_HEIGHT/*, leftEarRotation, EAR_WIDTH/2, EAR_HEIGHT*/);
        
        /* head */
        renderer::glRenderCircle(skinColor, posX, posY, width, height);

        
        /* eyes */
        const float EYE_WIDTH = 8;
        float EYE_HEIGHT = 20;
        if (isBlinking) {
            EYE_HEIGHT = 3;
        }
        const float EYE_DISTANCE = 10;
        const float EYE_OFFSET = 6;
        SDL_Color eyeColor = { 0, 0, 0, 255 };
        
        float eyePosY = posY + height/2 - EYE_HEIGHT/2 + 4;
        float eyePosX = posX + width/2 - EYE_WIDTH/2;
        if (facingLeft) eyePosX -= EYE_OFFSET;
        else eyePosX += EYE_OFFSET;
        
        renderer::glRenderCircle(eyeColor, eyePosX - EYE_DISTANCE/2, eyePosY, EYE_WIDTH, EYE_HEIGHT);
        renderer::glRenderCircle(eyeColor, eyePosX + EYE_DISTANCE/2, eyePosY, EYE_WIDTH, EYE_HEIGHT);


        /* right (front) ear */
        renderer::glRenderCircle(skinColor, earPosX - EAR_DISTANCE/2, posY + height - EAR_OFFSET_Y, EAR_WIDTH, EAR_HEIGHT /*, rightEarRotation, EAR_WIDTH/2, EAR_HEIGHT*/);
        
        if (facingLeft) {
            leftEarRotation *= -1;
            rightEarRotation *= -1;
        }
    }
    else if (isDead) {
        renderer::glRenderRect({ 255, 0, 0, 150 }, posX - 1000, posY - 1000, 2000, 2000);
    }
}


void Player::resolveHitboxes() {
    onGround = false;
    
    bool collideX = false;
    bool collideY = false;
    

    if (posY < -400) {
        setDead();
    }
    
    if (STATIC_SCREEN) {
        if (posX > SCREEN_WIDTH) {
            posX = -width;
        } if (posX < -width) {
            posX = SCREEN_WIDTH;
        }
    }
    
    

    for (int i = 0; i < objects.size(); i++) {
        BaseObject rect;
        /*
        if (i == rectangles.size()) {
            if (isPlayer2) {
                rect = player;
            } else {
                rect = player2;
            }
        } else {
        }*/
        rect = objects.at(i);

        double highestDistance = max(fabs(velocityX) * projectMain.secondsPassed, fabs(velocityY) * projectMain.secondsPassed);
        
        for (int i2 = 0; i2 < highestDistance; i2++) {
            double timePassed;
            if (fabs(velocityX) > fabs(velocityY)) {
                timePassed = i2 / fabs(velocityX);
            } else {
                timePassed = i2 / fabs(velocityY);
            }
            
            int c = collidesWith(rect, timePassed);
            if (c != 0) {
                if (c == 1) {  /* left */
                    posX = rect.posX - width;
                    collideX = true;
                    velocityX = 0;
                } else if (c == 2) {  /* right */
                    posX = rect.posX + rect.width;
                    collideX = true;
                    velocityX = 0;
                } else if (c == 3) {  /* bottom */
                    posY = rect.posY - height;
                    collideY = true;
                    velocityY = 0;
                } else if (c == 4) {  /* top */
                    posY = rect.posY + rect.height;
                    collideY = true;
                    onGround = true;
                }
                break;
            }
        }
    }
    
    if (collideX) {
        velocityX = 0;
    }
    
    if (collideY) {
        velocityY *= -0.5;
        if (fabs(velocityY) < 50) {
            velocityY = 0;
        }
    }
}


void Player::setDead() {
    isDead = true;
}


void Player::respawn() {
    
    isDead = false;
    posX = 0;
    posY = 400;
    
    velocityX = 0;
    velocityY = 0;
}





