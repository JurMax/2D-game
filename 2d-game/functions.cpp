//
//  functions.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "functions.hpp"

const bool SCREEN_REPEAT = true;
const bool STATIC_SCREEN = false;
const bool SHOW_MOUSE = true;

const bool IS_DEBUG = true;


float getMouseX() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (float) (x) / ((float) SCREEN_WIDTH / 100.0f) + projectMain.cameraOffsetX + projectMain.debugCameraOffsetX;
}

float getMouseY() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (float) (-y) / ((float) SCREEN_WIDTH / 100.0f) + projectMain.cameraOffsetY + projectMain.debugCameraOffsetY + 77.5;
}



void printError(std::string str) {
    if (IS_DEBUG) {
        std::string errorString = "ERROR: " + str;
        cout << errorString << endl;
    }
}



void loadShader(int shaderType) {
    bool isVertex = shaderType == GL_VERTEX_SHADER;
    
    GLuint *shader;
    if (isVertex) {
        shader = &projectMain.vertexShader;
    } else {
        shader = &projectMain.fragmentShader;
    }
    *shader = glCreateShader(shaderType);

    
    string fileName = "";
    fileName.append(SDL_GetBasePath());
    if (isVertex) fileName += "vertex.c";
    else fileName += "fragment.c";
    
    std::string str = getFileContents(fileName.c_str());
    char *c_str = new char[str.length()+1];
    std::strcpy(c_str, str.c_str());
    
    
    const GLchar *shaderSource[] = { c_str };
    
    glShaderSource(*shader, 1, shaderSource, NULL);
    glCompileShader(*shader);
    
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &shaderCompiled);
    
    if (shaderCompiled != GL_TRUE) {
        string shaderstr;
        if (isVertex) shaderstr = "vertex";
        else shaderstr = "fragment";
        
        printf("Unable to compile %s shader [%d]:\n", shaderstr.c_str(), *shader);

        int infoLogLength = 0;
        int maxLength = infoLogLength;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &maxLength);
        
        char* infoLog = new char[maxLength];
        glGetShaderInfoLog(*shader, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0) {
            printf("%s\n", infoLog);
        }
        delete[] infoLog;
    }
    
    glAttachShader(projectMain.glProgram, *shader);
}


std::string getFileContents(const char *filename) {
    FILE *file = std::fopen(filename, "r");
    if (file) {
        string contents;
        std::fseek(file, 0, SEEK_END);
        contents.resize(std::ftell(file));
        std::rewind(file);
        std::fread(&contents[0], 1, contents.size(), file);
        std::fclose(file);
        return(contents);
    }
    throw(errno);
}


