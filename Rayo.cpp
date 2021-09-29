#include "Rayo.h"

vec3f Rayo::punto_interseccion(float t) {
    return ori + dir*t;
}
