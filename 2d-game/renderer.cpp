//
//  renderer.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 25-04-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "renderer.hpp"


namespace renderer {
    
    bool rendererIntialisationSucces = true;
    
    bool antialiasEnabled = false;
    float antialiasSize = 0.9;
    float screenScale = 1.0;

    
    GLuint glProgram;
    
    GLuint glUniform_screenSize = -1;
    GLuint glUniform_screenPos = -1;
    GLuint glUniform_screenScale = -1;
    GLuint glUniform_texture = -1;
    GLuint glUniform_settings = -1;
    
    GLuint glUniform_shapePos = -1;
    GLuint glUniform_shapeRotation = -1;
    GLuint glUniform_shapeRotationPoint = -1;

    
    GLuint glAttrib_position = -1;
    GLuint glAttrib_color = -1;
    GLuint glAttrib_textureCoords = -1;
    GLuint glAttrib_barycentric = -1;


    GLuint m_vbo[ATTRIB_COUNT], m_vao[1];

    
    bool initializeRenderer() {
        
        antialiasSize = antialiasSize * (SCREEN_WIDTH/SCREEN_HEIGHT);
        
        glProgram = projectMain.glProgram;
        
        glGenBuffers(ATTRIB_COUNT, m_vbo);
        glGenVertexArrays(1, m_vao);
        glBindVertexArray(m_vao[0]);
        
        
        loadUniformLocation(&glUniform_screenSize, "u_screenSize");
        loadUniformLocation(&glUniform_screenPos, "u_screenOffset");
        loadUniformLocation(&glUniform_screenScale, "u_screenScale");
        loadUniformLocation(&glUniform_settings, "u_settings");

        loadUniformLocation(&glUniform_texture, "u_shapeTexture");
        loadUniformLocation(&glUniform_shapePos, "u_shapePos");
        loadUniformLocation(&glUniform_shapeRotation, "u_shapeRotation");
        loadUniformLocation(&glUniform_shapeRotationPoint, "u_shapeRotationPoint");

        
        loadAttributeLocation(&glAttrib_position, "vertexPos");
        loadAttributeLocation(&glAttrib_color, "vertexColor");
        loadAttributeLocation(&glAttrib_textureCoords, "vertexTexCoord");
        loadAttributeLocation(&glAttrib_barycentric, "vertexBarycentric");
        
        
        return rendererIntialisationSucces;
    }
    
    
    void loadUniformLocation(GLuint *uniform, string location) {
        GLuint i = glGetUniformLocation(glProgram, location.c_str());
        *uniform = i;
        if(*uniform == -1) {
            printError(location + " (uniform) is not a valid glsl program variable!");
            rendererIntialisationSucces = false;
        }
    }
    
    
    void loadAttributeLocation(GLuint *attribute, string location) {
        GLuint i = glGetAttribLocation(glProgram, location.c_str());
        *attribute = i;
        if(*attribute == -1) {
            printError(location + " (attribute) is not a valid glsl program variable!");
            rendererIntialisationSucces = false;
        }
        glEnableVertexAttribArray(*attribute);
    }
    
    
    void cleanup() {
        glDisableVertexAttribArray(0);
        glDeleteBuffers(ATTRIB_COUNT, m_vbo);
        glDeleteVertexArrays(1, m_vao);
    }
    
    
    
    void setUniforms() {
        float screenSize[] = { (float) SCREEN_WIDTH, (float) SCREEN_HEIGHT };
        glUniform2fv(glUniform_screenSize, 1, screenSize);
        
        float screenOffset[] = {
            - projectMain.cameraOffsetX - projectMain.debugCameraOffsetX,
            - projectMain.cameraOffsetY - projectMain.debugCameraOffsetY
        };
        glUniform2fv(glUniform_screenPos, 1, screenOffset);
        
        
        if (IS_DEBUG) {
            if (isKeyDown(SDL_SCANCODE_COMMA)) screenScale += 0.05;
            if (isKeyDown(SDL_SCANCODE_PERIOD)) screenScale -= 0.05;
            if (isKeyDown(SDL_SCANCODE_SLASH)) {
                screenScale = 1.0;
                projectMain.debugCameraOffsetX = 0;
                projectMain.debugCameraOffsetY = 0;
            }
            glUniform1f(glUniform_screenScale, screenScale);
        }

        if (isKeyPressed(SDL_SCANCODE_L)) {
            antialiasEnabled = !antialiasEnabled;
        }
        float settings[] = { (float) antialiasEnabled, 1.0f, 1.0f, 1.0f };
        glUniform4fv(glUniform_settings, 1, settings);
    }

    
    
    void glRenderRect(SDL_Color color, float posX, float posY, float width, float height) {
        glRenderRect(r::texture_Blank, color, posX, posY, width, height, 0.0, NULL, NULL);
    }
    
    void glRenderRect(GLuint texture, SDL_Color color, float posX, float posY, float width, float height) {
        glRenderRect(texture, color, posX, posY, width, height, 0.0, NULL, NULL);
    }
    
    void glRenderRect(GLuint texture, SDL_Color color, float posX, float posY, float width, float height, float rotation, float *rotX, float *rotY) {
        const int points = 6;
        
        float rotationPointX;
        float rotationPointY;
        
        if (rotX == NULL) rotationPointX = width/2;
        else rotationPointX = *rotX;
        if (rotY == NULL) rotationPointY = height/2;
        else rotationPointY = *rotY;
        
        
        GLfloat position[] = {
            posX, posY
        };

        GLfloat square[points * FLOATS_PER_POINT] = {
           0,     height,  // Top left
           width, height,  // Top right
           width, 0,       // Bottom right
           
           width, 0,       // Bottom right
           0,     0,       // Bottom left
           0,     height   // Top left
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
        
        GLfloat rotationPoint[] = {
            rotationPointX, rotationPointY
        };
        
        glUniform2fv(glUniform_shapePos, 1, position);
        glUniform1f(glUniform_shapeRotation, rotation);
        glUniform2fv(glUniform_shapeRotationPoint, 1, rotationPoint);
        glRenderArrays(points, square, colors, texturecoords, barycentric, texture);
    }
    
    
    void glRenderCircle(SDL_Color color, float posX, float posY, float width, float height) {
        const int triangles = 48;
        const int points = triangles * 3;
        const float DEG2RAD = 3.14159265359 / 180;

        if (antialiasEnabled) {
            posX -= antialiasSize / 2;
            posY -= antialiasSize / 2;
            width += antialiasSize;
            height += antialiasSize;
        }
        
        GLfloat position[] = {
            posX, posY
        };
        
        GLfloat circle[points * FLOATS_PER_POINT];
        GLfloat colors[points * FLOATS_PER_COLOR];
        GLfloat textureCoords[points * FLOATS_PER_TEX_COORD];
        GLfloat barycentric[points * FLOATS_PER_BARYCENTRIC];
        
        for (int i = 0; i < points; i += 3) {
            float fp = points;
            float fi = i;
            float degInRad = (360.0f / fp * fi) * DEG2RAD;
            float degInRadNext = (360.0f / fp * (fi + 3)) * DEG2RAD;
            
            circle[(i + 0) * 2 + 0] = width/2;
            circle[(i + 0) * 2 + 1] = height/2;
            circle[(i + 1) * 2 + 0] = cos(degInRad) * (width/2) + (width/2);
            circle[(i + 1) * 2 + 1] = sin(degInRad) * (height/2) + (height/2);
            circle[(i + 2) * 2 + 0] = cos(degInRadNext) * (width/2) + (width/2);
            circle[(i + 2) * 2 + 1] = sin(degInRadNext) * (height/2) + (height/2);
            
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
        

        GLfloat rotationPoint[] = { width/2, height/2 };
        glUniform2fv(glUniform_shapePos, 1, position);
        glUniform2fv(glUniform_shapeRotationPoint, 1, rotationPoint);
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
        
        // texture //
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
    
    
    
    void renderText(string str, SDL_Color color, float posX, float posY, float maxWidth, float lineHeight, bool alignleft) {
        int tcharacterwidths[] = {
            3,5,8,8,8,8,3,4,4,5,7,4,8,3,8, 8,8,8,8,8,
            8,8,8,8,8, 3,4,5,8,5,8,8, 8,8,8,8,8,
            8,8,8,5,8,8,8,8,8,8,8,8,8,8,8,8,
            8,8,8,8,8, 4,8,4,7,8,4, 6,
            
            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
            8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8
        };
        const int tcharacterheight = 8;
        
        int texturesize = 128;
        
        const int points = (int) str.length() * 6;
        
        GLfloat position[] = {
            posX, posY
        };
        
        GLfloat text[points * FLOATS_PER_POINT];
        GLfloat colors[points * FLOATS_PER_COLOR];
        GLfloat textureCoords[points * FLOATS_PER_TEX_COORD];
        GLfloat barycentric[points * FLOATS_PER_BARYCENTRIC];
        
        
        float offsetx = 0;
        float offsety = 0;

        for (int i = 0; i < str.length(); i++) {
            int c = (int) str.c_str()[i] - 33;
            
            if (c <= -1) {  // char is a space
                offsetx += lineHeight;
            }
            else {
                float cwidth = (float) tcharacterwidths[c] / (float) tcharacterheight * (float) lineHeight;
                float cheight = lineHeight;
                
                if (maxWidth != 0) {
                    if (offsetx + cwidth >= maxWidth) {
                        offsetx = 0;
                        offsety -= lineHeight;
                    }
                }
            
                text[i*12 + 0] = offsetx;          text[i*12 + 1] = offsety + cheight;
                text[i*12 + 2] = offsetx + cwidth; text[i*12 + 3] = offsety + cheight;
                text[i*12 + 4] = offsetx + cwidth; text[i*12 + 5] = offsety;

                text[i*12 + 6] = offsetx + cwidth; text[i*12 + 7] = offsety;
                text[i*12 + 8] = offsetx;          text[i*12 + 9] = offsety;
                text[i*12 +10] = offsetx;          text[i*12 +11] = offsety + cheight;
            
                offsetx += cwidth;

                for (int i2 = 0; i2 < 6; i2++) {
                    colors[i*24 + i2*4 + 0] = (float) (color.r) / 255.0f;
                    colors[i*24 + i2*4 + 1] = (float) (color.g) / 255.0f;
                    colors[i*24 + i2*4 + 2] = (float) (color.b) / 255.0f;
                    colors[i*24 + i2*4 + 3] = (float) (color.a) / 255.0f;
                }
            
                int textureposx = 0;
                int textureposy = 0;

                for (int i2 = 0; i2 <= c; i2++) {
                    textureposx += tcharacterwidths[i2];
                
                    if (textureposx > texturesize) {
                        textureposx = tcharacterwidths[i2];
                        textureposy += tcharacterheight;
                    }
                }
        
                textureposx -= tcharacterwidths[c];
                
                
                float left = (float) (textureposx) / (float) (texturesize);
                float right = (float) (textureposx + tcharacterwidths[c]) / (float) (texturesize);
                float top = (float) (textureposy) / (float) (texturesize);
                float bottom = (float) (textureposy + tcharacterheight) / (float) (texturesize);
            
                textureCoords[i*12 + 0] = left;  textureCoords[i*12 + 1] = top;
                textureCoords[i*12 + 2] = right; textureCoords[i*12 + 3] = top;
                textureCoords[i*12 + 4] = right; textureCoords[i*12 + 5] = bottom;

                textureCoords[i*12 + 6] = right; textureCoords[i*12 + 7] = bottom;
                textureCoords[i*12 + 8] = left;  textureCoords[i*12 + 9] = bottom;
                textureCoords[i*12 +10] = left;  textureCoords[i*12 +11] = top;
                
            }
            
        }
        
        glUniform2fv(glUniform_shapePos, 1, position);
        glRenderArrays(points, text, colors, textureCoords, barycentric, r::texture_Font);
    }
    
}



