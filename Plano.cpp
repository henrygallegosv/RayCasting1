#include "Plano.h"

Plano::Plano(vec3f _punto, vec3f _normal, vec3f _color, vec3f _kdkskr, float _n) : punto{_punto}, normal{_normal}, Objeto(_color, _kdkskr,_n)
{
    normal.normalize();
}

bool Plano::intersectar(Rayo ray, float &t, vec3f &c, vec3f &_normal) {
    t = normal.productoPunto(punto-ray.ori)/ normal.productoPunto(ray.dir);
    if ( t > 0.0001 ) {
        _normal = normal;
        c = color;
        return true;
    }
    return false;
}
