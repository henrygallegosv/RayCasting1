#ifndef RT1_ESFERA_H
#define RT1_ESFERA_H
#include "Objeto.h"
class Esfera : public Objeto {
public:
    vec3f centro;
    float radio;

    Esfera(vec3f cen, float r, vec3f col, vec3f _kdkskr, float _n);
    bool intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal) override;
};

#endif //RT1_ESFERA_H
