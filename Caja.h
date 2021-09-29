#ifndef RT1_CAJA_H
#define RT1_CAJA_H

class Caja : public Objeto {
public:
    vec3f rad;
    Caja(vec3f _rad, vec3f col, vec3f _kdkskr, float _n);

    bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &normal) override{}
};

#endif //RT1_CAJA_H
