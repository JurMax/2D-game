//
//  functions.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include "projectmain.hpp"


#define FLOATS_PER_POINT 2
#define FLOATS_PER_COLOR 4
#define FLOATS_PER_TEX_COORD 2
#define FLOATS_PER_BARYCENTRIC 3
#define ATTRIB_COUNT 4


extern const bool SCREEN_REPEAT;
extern const bool STATIC_SCREEN;
extern const bool SHOW_MOUSE;

extern const bool IS_DEBUG;


//extern const uint32_t FLOATS_PER_POINT = 3;
//extern const uint32_t FLOATS_PER_COLOR = 4;


int getMouseX();
int getMouseY();
void printError(std::string str);

void loadShader(int shaderType);
std::string getFileContents(const char *filename);


#endif /* functions_hpp */
