//
// Created by davla on 28/09/2021.
//

#ifndef RT1_PLANO_H
#define RT1_PLANO_H

class Plano : public Objeto {
public:
    vec3f punto, normal;

    Plano(vec3f _punto, vec3f _normal, vec3f _color, vec3f _kdkskr, float _n) : punto{_punto}, normal{_normal}, Objeto(_color, _kdkskr,_n)
    {
        normal.normalize();
    }

    bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &_normal) {
        t = normal.productoPunto(punto-ray.ori)/ normal.productoPunto(ray.dir);
        if ( t > 0.0001 ) {
            _normal = normal;
            c = color;
            return true;
        }
        return false;
    }
};


#endif //RT1_PLANO_H
