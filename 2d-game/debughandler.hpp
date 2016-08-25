//
//  debughandler.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-08-16.
//  Copyright © 2016 JurMax. All rights reserved.
//

#ifndef debughandler_hpp
#define debughandler_hpp

#include "projectmain.hpp"


class debugPrimitive {
public:
    string name;
    int valueType;  // 0 for int, 1 for bool, 2 for float
    
    int *intValue;
    bool *boolValue;
    float *floatValue;
};



namespace debug {
    
    void update();
    void render();
    
    debugPrimitive add(int* value, string name);
    debugPrimitive add(bool* value, string name);
    debugPrimitive add(float* value, string name);
    void removeDuplicates();
    
    string debugToString(int i);
}

#endif /* debughandler_hpp */


