//
// Created by henry on 8/09/2021.
//

#include "vector.h"
#include <iostream>
std::ostream& operator<<(std::ostream &os, vec3f v){
    os << "[" << v.x << ", " << v.y << "," << v.z << "]";
    return os;
}

vec3f operator/(float f, vec3f &v) {
    if (v.x == 0 || v.y == 0 || v.z == 0) {
        std::cout << "Hay cero";
    }
    float tx = (v.x == 0) ? f/0.01 : f/v.x;
    float ty = (v.y == 0) ? f/0.01 : f/v.y;
    float tz = (v.z == 0) ? f/0.01: f/v.z;

    return vec3f(tx, ty, tz);
}

vec3f abs(vec3f &v) {
    return vec3f( abs(v.x), abs(v.y), abs(v.z) );
}
vec3f sign(vec3f &v) {
    return vec3f( sgn(v.x), sgn(v.y), abs(v.z) );
}
vec3f step(vec3f v1, vec3f v2) {
    return vec3f(v2.x < v1.x ? 0 : 1,
                 v2.y < v1.y ? 0 : 1,
                 v2.z < v1.z ? 0 : 1);
}