//
// Created by henry on 9/09/2021.
//

#ifndef RT1_RAYO_H
#define RT1_RAYO_H

#include "vector.h"

class Rayo {
public:
    vec3f ori, dir;

    Rayo() {}

    vec3f punto_interseccion(float t) {
        return ori + dir*t;
    }
};


#endif //RT1_RAYO_H
