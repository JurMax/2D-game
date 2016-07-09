//
//  renderer.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 25-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "renderer.hpp"


namespace renderer {
    
    GLuint glProgram;
    
    GLuint glUniform_screenSize = -1;
    GLuint glUniform_screenPos = -1;
    GLuint glUniform_texture = -1;
    GLuint glUniform_settings = -1;
    
    GLuint glAttrib_position = -1;
    GLuint glAttrib_color = -1;
    GLuint glAttrib_textureCoords = -1;
    GLuint glAttrib_barycentric = -1;


    GLuint m_vbo[ATTRIB_COUNT], m_vao[1];
    
    bool initializeRenderer() {
        bool succes = true;
        
        glProgram = projectMain.glProgram;
        
        glUniform_screenSize = glGetUniformLocation(glProgram, "u_screenSize");
        if(glUniform_screenSize == -1) {
            printError("u_screenSize is not a valid glsl program variable!");
            succes = false;
        }
        glUniform_screenPos = glGetUniformLocation(glProgram, "u_screenOffset");
        if(glUniform_screenPos == -1) {
            printError("u_screenOffset is not a valid glsl program variable!");
            succes = false;
        }
        glUniform_texture = glGetUniformLocation(glProgram, "u_texture");
        if(glUniform_texture == -1) {
            printError("u_texture is not a valid glsl program variable!");
            succes = false;
        }
        glUniform_settings = glGetUniformLocation(glProgram, "u_settings");
        if(glUniform_settings == -1) {
            printError("u_settings is not a valid glsl program variable!");
            succes = false;
        }
        
        
        glAttrib_position = glGetAttribLocation(glProgram, "vertexPos2D");
        if(glAttrib_position == -1) {
            printError("vertexPos2D is not a valid glsl program variable!");
            succes = false;
        }
        glAttrib_color = glGetAttribLocation(glProgram, "vertexColor");
        if(glAttrib_color == -1) {
            printError("vertexColor is not a valid glsl program variable!");
            succes = false;
        }
        glAttrib_textureCoords = glGetAttribLocation(glProgram, "vertexTexCoord");
        if(glAttrib_textureCoords == -1) {
            printError("vertexTexCoord is not a valid glsl program variable!");
            succes = false;
        }
        glAttrib_barycentric = glGetAttribLocation(glProgram, "vertexBarycentric");
        if(glAttrib_barycentric == -1) {
            printError("vertexBarycentric is not a valid glsl program variable!");
            succes = false;
        }
        
        
        
        glGenBuffers(ATTRIB_COUNT, m_vbo);
        glGenVertexArrays(1, m_vao);
        glBindVertexArray(m_vao[0]);
        glEnableVertexAttribArray(glAttrib_position);
        glEnableVertexAttribArray(glAttrib_color);
        glEnableVertexAttribArray(glAttrib_textureCoords);
        glEnableVertexAttribArray(glAttrib_barycentric);

        
        return succes;
    }
    
    
    void cleanup() {
        glDisableVertexAttribArray(0);
        glDeleteBuffers(ATTRIB_COUNT, m_vbo);
        glDeleteVertexArrays(1, m_vao);
    }
    
    
    void setUniforms() {
        float screenSize[] = { (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT };
        glUniform2fv(glUniform_screenSize, 1, screenSize);
        
        float screenOffset[] = { (float) projectMain.screenOffsetX, (float) projectMain.screenOffsetY };
        glUniform2fv(glUniform_screenPos, 1, screenOffset);

        static bool antialiasEnabled = false;
        if (isKeyPressed(SDL_SCANCODE_L)) {
            antialiasEnabled = !antialiasEnabled;
        }
        float settings[] = { (float) antialiasEnabled, 1.0f, 1.0f, 1.0f };
        glUniform4fv(glUniform_settings, 1, settings);
    }

    
    
    void glRenderRect(SDL_Color color, float posX, float posY, float width, float height) {
        const int points = 6;
        
        GLfloat square[points * FLOATS_PER_POINT] = {
           posX        ,  posY + height,  // Top left
           posX + width,  posY + height,  // Top right
           posX + width,  posY,           // Bottom right
            
           posX + width,  posY,           // Bottom right
           posX        ,  posY,           // Bottom left
           posX        ,  posY + height   // Top left
        };
        
        GLfloat colors[points * FLOATS_PER_COLOR] = {
           (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Top left
           (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Top right
           (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Bottom right
            
           (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Bottom right
           (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255,  // Bottom left
           (float) (color.r)/255, (float) (color.g)/255, (float) (color.b)/255, (float) (color.a)/255   // Top left
        };
        
        GLfloat texturecoords[points * FLOATS_PER_TEX_COORD] = {
           0.0f, 0.0f,  // Top left
           1.0f, 0.0f,  // Top right
           1.0f, 1.0f,  // Bottom right
            
           1.0f, 1.0f,  // Bottom right
           0.0f, 1.0f,  // Bottom left
           0.0f, 0.0f   // Top left
        };
        
        GLfloat barycentric[points * FLOATS_PER_BARYCENTRIC] = {
            1.0f, 0.0f, 0.0f,  // Top left
            0.0f, 1.0f, 0.0f,  // Top right
            0.0f, 0.0f, 1.0f,  // Bottom right
            
            1.0f, 0.0f, 0.0f,  // Bottom right
            0.0f, 1.0f, 0.0f,  // Bottom left
            0.0f, 0.0f, 1.0f   // Top left
        };
        
        glRenderArrays(points, square, colors, texturecoords, barycentric, r::texture_Blank);
    }
    
    
    void glRenderCircle(SDL_Color color, float posX, float posY, float width, float height) {
        const int vertices = 48;
        const int points = vertices * 3;
        const float DEG2RAD = 3.14159265359 / 180;
        
        GLfloat circle[points * FLOATS_PER_POINT];
        GLfloat colors[points * FLOATS_PER_COLOR];
        GLfloat textureCoords[points * FLOATS_PER_TEX_COORD];
        GLfloat barycentric[points * FLOATS_PER_BARYCENTRIC];
        
        for (int i = 0; i < points; i += 3) {
            if (isKeyPressed(SDL_SCANCODE_P)) {
                cout << i << endl;
            }
            float fp = points;
            float fi = i;
            float degInRad = (360.0f / fp * fi) * DEG2RAD;
            float degInRadNext = (360.0f / fp * (fi + 3)) * DEG2RAD;
            
            circle[(i + 0) * 2 + 0] = posX + width/2;
            circle[(i + 0) * 2 + 1] = posY + height/2;
            circle[(i + 1) * 2 + 0] = cos(degInRad) * (width/2) + (width/2) + posX;
            circle[(i + 1) * 2 + 1] = sin(degInRad) * (height/2) + (height/2) + posY;
            circle[(i + 2) * 2 + 0] = cos(degInRadNext) * (width/2) + (width/2) + posX;
            circle[(i + 2) * 2 + 1] = sin(degInRadNext) * (height/2) + (height/2) + posY;
            
            for (int i2 = 0; i2 < 3; i2++) {
                colors[(i + i2) * 4 + 0] = (float) (color.r) / 255.0f;
                colors[(i + i2) * 4 + 1] = (float) (color.g) / 255.0f;
                colors[(i + i2) * 4 + 2] = (float) (color.b) / 255.0f;
                colors[(i + i2) * 4 + 3] = (float) (color.a) / 255.0f;
            }
            
            textureCoords[(i + 0) * 2 + 0] = -0.5f;
            textureCoords[(i + 0) * 2 + 1] = 0.5f;
            textureCoords[(i + 1) * 2 + 0] = (cos(degInRad)/2 - 0.5f);
            textureCoords[(i + 1) * 2 + 1] = (0.5f - sin(degInRad)/2);
            textureCoords[(i + 2) * 2 + 0] = (cos(degInRadNext)/2 - 0.5f);
            textureCoords[(i + 2) * 2 + 1] = (0.5f - sin(degInRadNext)/2);

            barycentric[(i + 0) * 3 + 0] = 1;
            barycentric[(i + 0) * 3 + 1] = 1;
            barycentric[(i + 0) * 3 + 2] = 1;
            barycentric[(i + 1) * 3 + 0] = 0;
            barycentric[(i + 1) * 3 + 1] = 1;
            barycentric[(i + 1) * 3 + 2] = 0;
            barycentric[(i + 2) * 3 + 0] = 0;
            barycentric[(i + 2) * 3 + 1] = 0;
            barycentric[(i + 2) * 3 + 2] = 1;
        }
        
        glRenderArrays(points, circle, colors, textureCoords, barycentric, r::texture_Blank);
    }

    
    
    void glRenderArrays(int points, GLfloat* vertices, GLfloat* colors, GLfloat* texturecoords, GLfloat* barycentric, GLuint texture) {
        
        glBindVertexArray(m_vao[0]);
        
        // position points //
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, (points * FLOATS_PER_POINT) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(glAttrib_position, FLOATS_PER_POINT, GL_FLOAT, GL_FALSE, 0, 0);
        
        // color //
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, (points * FLOATS_PER_COLOR) * sizeof(GLfloat), colors, GL_STATIC_DRAW);
        glVertexAttribPointer(glAttrib_color, FLOATS_PER_COLOR, GL_FLOAT, GL_FALSE, 0, 0);
        
        // texture coords //
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[2]);
        glBufferData(GL_ARRAY_BUFFER, (points * FLOATS_PER_TEX_COORD) * sizeof(GLfloat), texturecoords, GL_STATIC_DRAW);
        glVertexAttribPointer(glAttrib_textureCoords, FLOATS_PER_TEX_COORD, GL_FLOAT, GL_FALSE, 0, 0);
        
        // texture ///
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glUniform_texture, 0);
        
        // barycentric //
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo[3]);
        glBufferData(GL_ARRAY_BUFFER, (points * FLOATS_PER_BARYCENTRIC) * sizeof(GLfloat), barycentric, GL_STATIC_DRAW);
        glVertexAttribPointer(glAttrib_barycentric, FLOATS_PER_BARYCENTRIC, GL_FLOAT, GL_FALSE, 0, 0);
        
        
        glDrawArrays(GL_TRIANGLES, 0, points);
        
        projectMain.glTriangleCount += points/3;
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
        
        const GLchar *shaderSource[] = { getFileContents(fileName.c_str()).c_str() };
        
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
    
    
    
    void renderText(TTF_Font* font, string str, int posx, int posy, SDL_Color color) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, str.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(projectMain.renderer, surfaceMessage);
        
        int stringwidth = 0, stringheight = 0;
        TTF_SizeText(font, str.c_str(), &stringwidth, &stringheight);
        
        SDL_Rect rect;
        rect.x = floor(posx);
        rect.y = floor(posy);
        rect.w = floor(stringwidth);
        rect.h = floor(stringheight);
        
        if (posx == -9999)  rect.x = SCREEN_WIDTH/2 - stringwidth/2;
        if (posy == -9999)  rect.y = SCREEN_HEIGHT/2 - stringheight/2;
        
        SDL_RenderCopy(projectMain.renderer, texture, NULL, &rect);
        
        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(texture);
    }
    
}



