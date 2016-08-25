//
//  baseobjects.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "baseobjects.hpp"


void BaseObject::update() {
    if (isMoving) {
        velocityX = 200;
    }
    
    posX += velocityX * projectMain.framerateModifier;
    posY += velocityY * projectMain.framerateModifier;
    velocityX *= 0.8;
    velocityY *= 0.8;
    
    
    if (SCREEN_REPEAT && STATIC_SCREEN) {
        int w, h;
        SDL_GetWindowSize(projectMain.window, &w, &h);
    
        if (posX > w) {
            posX = -width;
        } if (posX < -width) {
            posX = w;
        }
    }
    
}


void BaseObject::onActivated() {
    
}


void BaseObject::render() {
    /*if (updateGLBuffers) {
        updateBuffers();
        updateGLBuffers = false;
    }
    
    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);*/
    
    if (isKeyDown(SDL_SCANCODE_H)) rotation += 0.01;
    if (isKeyDown(SDL_SCANCODE_J)) rotation -= 0.01;

    float point = 0.0;
    renderer::glRenderRect(r::texture_Blank, debugColor, posX, posY, width, height, rotation, &point, &point);
    
}


void BaseObject::setBaseObject(float posx, float posy, float width, float height) {
    this->posX = posx;
    this->posY = posy;
    this->width = width;
    this->height = height;
    this->chunkID = -1;
    
    updateGLBuffers = true;
}


void BaseObject::updateBuffers() {
    const uint32_t points = 4;
    
    GLfloat square[points][FLOATS_PER_POINT] = {
        {  posX         ,  posY + height  }, // Top left
        {  posX + width ,  posY + height  }, // Top right
        {  posX + width ,  posY           }, // Bottom right
        {  posX         ,  posY           }, // Bottom left
    };
    const GLfloat colors[points][FLOATS_PER_COLOR] = {
        { (float) (debugColor.r)/255, (float) (debugColor.g)/255, (float) (debugColor.b)/255, (float) (debugColor.a)/255 }, // Top left
        { (float) (debugColor.r)/255, (float) (debugColor.g)/255, (float) (debugColor.b)/255, (float) (debugColor.a)/255 }, // Top right
        { (float) (debugColor.r)/255, (float) (debugColor.g)/255, (float) (debugColor.b)/255, (float) (debugColor.a)/255 }, // Bottom right
        { (float) (debugColor.r)/255, (float) (debugColor.g)/255, (float) (debugColor.b)/255, (float) (debugColor.a)/255 }, // Bottom left
    };
    
    glBindVertexArray(vao[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, (points * FLOATS_PER_POINT) * sizeof(GLfloat), square, GL_STATIC_DRAW);
    glVertexAttribPointer(renderer::glAttrib_position, FLOATS_PER_POINT, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, (points * FLOATS_PER_COLOR) * sizeof(GLfloat), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(renderer::glAttrib_color, FLOATS_PER_COLOR, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(renderer::glAttrib_position);
    glEnableVertexAttribArray(renderer::glAttrib_color);
}


void BaseObject::destroy() {
    glDisableVertexAttribArray(0);
    glDeleteBuffers(ATTRIB_COUNT, vbo);
    glDeleteVertexArrays(1, vao);
}


/** returns int =>
 * 0: not colliding
 * 1: collides left  2: collides right  3: collides bottom  4: collides top */
int BaseObject::collidesWith(BaseObject obj, float timePassed) {
    
    double posx = posX - velocityX * projectMain.framerateModifier + velocityX * timePassed;
    double posy = posY - velocityY * projectMain.framerateModifier + velocityY * timePassed;
    
    bool sameX = posx + width > obj.posX && posx < obj.posX + obj.width;
    bool sameY = posy + height > obj.posY && posy < obj.posY + obj.height;
    
    if (sameX && sameY) {
        double overlapX;
        if (posX < obj.posX) {
            overlapX = (posX + width) - (obj.posX);
        } else {
            overlapX = (obj.posX + obj.width) - (posX);
        }
        
        double overlapY;
        if (posY < obj.posY) {
            overlapY = (posY + height) - (obj.posY);
        } else {
            overlapY = (obj.posY + obj.height) - (posY);
        }
        
        double distX = (posx + width/2) - (obj.posX + obj.width/2);
        double distY = (posy + height/2) - (obj.posY + obj.height/2);
        
        if (distX < 0) distX *= -1;
        if (distY < 0) distY *= -1;
        distX -= width/2;
        distY -= height/2;
        
        if (distX > distY) {
            if (posx + width/2 < obj.posX + obj.width/2) {
                return 1;
            } else {
                return 2;
            }
        } else {
            if (posy + height/2 < obj.posY + obj.height/2) {
                return 3;
            } else {
                return 4;
            }
        }
    }
    return 0;
}



BaseObject createBaseObject(float posx, float posy, float width, float height) {
    BaseObject object;
    object.setBaseObject(posx, posy, width, height);
    
    glGenBuffers(ATTRIB_COUNT, object.vbo);
    glGenVertexArrays(1, object.vao);

    
    return object;
}




