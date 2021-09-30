#ifndef RT1_OBJETO_H
#define RT1_OBJETO_H

#include "vector.h"
#include "Rayo.h"

class Objeto {
public:
    vec3f color;
    vec3f kdkskr;
    float kt;  // refraccion o transmission
    bool es_reflexivo, es_refractivo;
    float eta, n;

    Objeto(vec3f col, vec3f _kdkskr, float _n);


    virtual bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &normal)=0;
};
#endif //RT1_OBJETO_H
