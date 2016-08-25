//
//  Jint.hpp
//  2d-game
//
//  Created by Jurriaan van den Berg on 10-08-16.
//  Copyright © 2016 JurMax. All rights reserved.
//


#ifndef jtypes_hpp
#define rt return *this;
#define jtypes_hpp

#include <stdio.h>


class Jint {
private:
    int i = 0;
    
public:
    int get();
    int set(int i2);

    
    Jint operator=(int i2)  { i = i2; rt }
    Jint operator+=(int i2)  { i += i2; rt }
    Jint operator-=(int i2)  { i -= i2; rt }
    
    Jint& operator++()  { i++; rt }
    Jint operator++(int i2)  { i++; rt }
    Jint& operator--()  { i--; rt }
    Jint operator--(int i2)  { i--; rt }
    
    operator int() const  { return i; }
};

inline Jint operator+(Jint lhs, const Jint& rhs) {
    lhs += rhs;
    return lhs;
}


#endif /* jtypes_hpp */


