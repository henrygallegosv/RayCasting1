//
// Created by henry on 8/09/2021.
//

#ifndef RT1_VECTOR_H
#define RT1_VECTOR_H

#include <cmath>
#include <ostream>

class vec3f {
public:
    float x, y, z;
    vec3f() {}

    vec3f(float _x, float _y, float _z):x{_x}, y{_y}, z{_z}{}

    void set(float _x, float _y, float _z) {
        x = _x;
        y = _y;
        z = _z;
    }

    vec3f productoCruz(vec3f v) {
        return vec3f(y*v.z - v.y*z, v.x*z - x*v.z, x*v.y - v.x*y);
        //return vec3f(y*v.z - v.y*z, x*v.z - v.x*z, x*v.y - v.x*y);
    }
    float productoPunto(vec3f v) {
        return x*v.x + y*v.y + z*v.z;
    }

    vec3f operator+(vec3f v) {
        return vec3f(x + v.x, y +v.y, z+v.z);
    }
    vec3f operator-(vec3f v) {
        return vec3f(x - v.x, y -v.y, z-v.z);
    }

    vec3f operator*(float f){
        return vec3f(f*x, f*y, f*z);
    }

    void operator*=(vec3f v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;
    }

    void normalize() {
        double m = modulo();
        x = x/m;
        y = y/m;
        z = z/m;
    }
    double modulo() {
        return sqrt(x*x + y*y + z*z);
    }

};
std::ostream& operator<<(std::ostream &os, vec3f v);



#endif //RT1_VECTOR_H
