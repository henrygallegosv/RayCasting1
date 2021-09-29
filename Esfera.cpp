#include "Esfera.h"

bool Esfera::intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal) {
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
