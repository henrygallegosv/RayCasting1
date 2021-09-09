//
// Created by henry on 9/09/2021.
//

#ifndef RT1_OBJETO_H
#define RT1_OBJETO_H

#include "vector.h"
#include "Rayo.h"

class Objeto {
public:
vec3f color;
Objeto(vec3f col):color{col}{}

virtual bool intersectar(Rayo ray, int &t, vec3f &c)=0;
};

class Esfera : public Objeto {
public:
    vec3f centro;
    float radio;

    Esfera(vec3f cen, float r, vec3f col): centro{cen}, radio{r}, Objeto(col) {}
    bool intersectar(Rayo ray, int &t, vec3f &col) {
        auto _a = ray.dir.productoPunto(ray.dir);
        auto _b = 2*ray.dir.productoPunto(ray.ori-centro);
        auto _c = (ray.ori-centro).productoPunto(ray.ori-centro)-radio*radio;
        auto D = _b*_b-4*_a*_c;
        if(D <= 0) {return false;}
        int t1 = (-_b + sqrt(D))/2*_a;
        int t2 = (-_b - sqrt(D))/2*_a;
        t = std::min(t1,t2);
        if(t <= 0) {return false;}
        col = color;
        return true;

    }
};


#endif //RT1_OBJETO_H
