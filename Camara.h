//
// Created by henry on 8/09/2021.
//

#ifndef RT1_CAMARA_H
#define RT1_CAMARA_H

#include "vector.h"
#include "CImg.h"

using namespace cimg_library;
typedef unsigned char BYTE;

class Camara {
    vec3f pos, xe, ye, ze;
    int w, h;
    float a, b, f, fov;

    CImg<BYTE> *pImg;

public:
    void calcularVectores(vec3f pos, vec3f center, vec3f up){
        this->pos = pos;
        ze = pos - center;
        ze.normalize();
        xe = ze.productoCruz(up);
        xe.normalize();
        ye = ze.productoCruz(xe);
    }
    void inicializar(int _w, int _h, float fov, float _near) {
        f = _near;
        w = _w;
        h = _h;
        a = 2 * f * tan(fov * M_PI/360);
        b = w / h * a;
    }

    void Renderizar();
};


#endif //RT1_CAMARA_H
