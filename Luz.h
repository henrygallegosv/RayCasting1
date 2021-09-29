#ifndef RT1_LUZ_H
#define RT1_LUZ_H

#include "vector.h"

class Luz {
public:
vec3f pos, color;

Luz() {}

Luz(vec3f _pos, vec3f _color);

void set(vec3f _pos, vec3f _color);
};


#endif //RT1_LUZ_H
