#ifndef RT1_CILINDRO_H
#define RT1_CILINDRO_H

#include "Objeto.h"

class Cilindro: public Objeto {
public:
    vec3f centro, pa, pb;
    float ra;

    Cilindro(vec3f _pa, vec3f _pb, float _radio, vec3f _color, vec3f _kdkskr, float _n);

    bool intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal) override;
};


#endif //RT1_CILINDRO_H