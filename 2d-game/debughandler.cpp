//
//  debughandler.cpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-08-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#include "debughandler.hpp"


namespace debug {
    
    vector<debugPrimitive> debugArray;
    int selected = 0;
    
    void update() {
        
        removeDuplicates();
        
        if (debugArray.size() != 0 && !isKeyDown(SDL_SCANCODE_C)) {
            
            if (isKeyPressed(SDL_SCANCODE_LEFT)) {
                selected -= 1;
                if (selected < 0)
                    selected = (int) debugArray.size() - 1;
                cout << "Selected_Debug: " << debugToString(selected) << endl;
            }
            if (isKeyPressed(SDL_SCANCODE_RIGHT)) {
                selected += 1;
                if (selected >= debugArray.size())
                    selected = 0;
                cout << "Selected_Debug: " << debugToString(selected) << endl;
            }
        
            if (isKeyPressed(SDL_SCANCODE_UP)) {
                cout << endl << "===== DEBUG_INFO =====" << endl;
                cout << " Debug_Size:" << debugArray.size() << endl;
                cout << " Selected_Debug: " << debugToString(selected) << endl;
            
                cout << " Debug_Items:" << endl;
                for (int i = 0; i < debugArray.size(); i++) {
                    cout << "  " << debugToString(i) << endl;
                }
            }
        
            if (isKeyPressed(SDL_SCANCODE_DOWN)) {
                debugPrimitive p = debugArray.at(selected);
                if (p.valueType == 0) {
                    *p.intValue = (int) inputHandler::getLastInputedNumber();
                }
                if (p.valueType == 1) {
                    *p.boolValue = (bool) inputHandler::getLastInputedNumber();
                }
                if (p.valueType == 2) {
                    *p.floatValue = inputHandler::getLastInputedNumber();
                }
                cout << " Debug_selected: " << debugToString(selected) << endl;
            }
        }
    }
    
    
    void render() {
        static float lineHeight = 4, maxWidth = 100;
        float onePixel = (float) lineHeight / (float) 8;
        
        renderer::renderText(inputHandler::getLine(), {0,0,0,255},
                             projectMain.cameraOffsetX + onePixel, 78-lineHeight-onePixel, maxWidth, lineHeight, false);
        renderer::renderText(inputHandler::getLine(), {255,255,255,255},
                             projectMain.cameraOffsetX, 78-lineHeight, maxWidth, lineHeight, false);
    }
    
    
    debugPrimitive add(int* value, string name) {
        debugPrimitive dp;
        dp.name = name;
        dp.valueType = 0;
        dp.intValue = value;
        debugArray.push_back(dp);
        return dp;
    }
    debugPrimitive add(bool* value, string name) {
        debugPrimitive dp;
        dp.name = name;
        dp.valueType = 1;
        dp.boolValue = value;
        debugArray.push_back(dp);
        return dp;
    }
    debugPrimitive add(float* value, string name) {
        debugPrimitive dp;
        dp.name = name;
        dp.valueType = 2;
        dp.floatValue = value;
        debugArray.push_back(dp);
        return dp;
    }
    
    
    void removeDuplicates() {
        int place = 0;
        
        for (int i = 0; i < debugArray.size(); i++) {
            place++;
            for (int i2 = place; i2 < debugArray.size(); i2++) {
                if (debugArray.at(i).name == debugArray.at(i2).name) {
                    debugArray.erase(debugArray.begin() + i2);
                }
            }
        }
    }
    

    string debugToString(int i) {
        debugPrimitive dp = debugArray.at(i);
        
        string value;
        if (dp.valueType == 0) value = to_string(*dp.intValue);
        else if (dp.valueType == 1) value = to_string(*dp.boolValue);
        else if (dp.valueType == 2) value = to_string(*dp.floatValue);
    
        return "[" + to_string(i) + "] " + dp.name + " = "+ value;
    }

}




