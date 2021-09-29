#ifndef RT1_PLANO_H
#define RT1_PLANO_H

#include "Objeto.h"

class Plano : public Objeto {
public:
    vec3f punto, normal;

    Plano(vec3f _punto, vec3f _normal, vec3f _color, vec3f _kdkskr, float _n);

    bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &_normal);
};


#endif //RT1_PLANO_H
