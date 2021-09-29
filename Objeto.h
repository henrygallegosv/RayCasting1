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
    vec3f kdkskr;
    bool es_reflexivo, es_refractivo;
    float nu, n;

    Objeto(vec3f col, vec3f _kdkskr, float _n) : n{_n},color{col}, kdkskr{_kdkskr}
    {
      //kd = ks = 0;
      es_reflexivo = es_refractivo = false;
    }

    //virtual bool intersectar(Rayo ray, int &t, vec3f &c)=0;
    virtual bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &normal)=0;
};
#endif //RT1_OBJETO_H
