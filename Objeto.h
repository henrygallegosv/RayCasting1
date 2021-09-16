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
float kd, ks, n;
Objeto(vec3f col):color{col}{}

//virtual bool intersectar(Rayo ray, int &t, vec3f &c)=0;
virtual bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &normal)=0;
};

class Esfera : public Objeto {
public:
    vec3f centro;
    float radio;

    Esfera(vec3f cen, float r, vec3f col): centro{cen}, radio{r}, Objeto(col) {}
    bool intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal) {
        auto _a = ray.dir.productoPunto(ray.dir);
        auto _b = 2*ray.dir.productoPunto(ray.ori-centro);
        auto _c = (ray.ori-centro).productoPunto(ray.ori-centro)-radio*radio;
        auto D = _b*_b-4*_a*_c;
        if(D <= 0) {return false;}
        float t1 = (-_b + sqrt(D))/2*_a;
        float t2 = (-_b - sqrt(D))/2*_a;
        t = std::min(t1, t2);
        if(t <= 0) {return false;}
        col = color;
        vec3f pi = ray.punto_interseccion(t);
        normal = pi - centro;
        normal.normalize();

        return true;

    }
};

class Cilindro: public Objeto {
public:
    vec3f centro;
    float yMin, yMax, radio;

    Cilindro(vec3f cen, float y_min, float y_max, float rad, vec3f _color):
    centro{cen}, yMin{y_min}, yMax{y_max}, radio{rad}, Objeto(_color) {}

    bool intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal) {
        auto _a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
        auto _b = 2 * (ray.dir.x * ray.ori.x + ray.dir.z * ray.ori.z );
        auto _c = ray.ori.x * ray.ori.x + ray.ori.z * ray.ori.z - radio * radio;

        auto D = _b*_b-4*_a*_c;
        if(D <= 0) {return false;}
        float t1 = (-_b + sqrt(D))/2*_a;
        float t2 = (-_b - sqrt(D))/2*_a;
        t = std::min(t1, t2);
        if(t <= 0) {return false;}
        col = color;
        vec3f pi = ray.punto_interseccion(t);
        if (pi.y < yMin || pi.y > yMax) { return false; }
        vec3f cen(centro.x, pi.y ,centro.z);
        normal = pi - cen;
        normal.normalize();

        return true;

    }
};


#endif //RT1_OBJETO_H
