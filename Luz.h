//
// Created by henry on 13/09/2021.
//

#ifndef RT1_LUZ_H
#define RT1_LUZ_H


#include "vector.h"

class Luz {
public:
vec3f pos, color;

Luz(vec3f _pos, vec3f _color) : pos{_pos}, color{_color} {}
};


#endif //RT1_LUZ_H
