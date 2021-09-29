//
// Created by henry on 8/09/2021.
//

#ifndef RT1_CAMARA_H
#define RT1_CAMARA_H

#include <iostream>
#include "vector.h"
#include "CImg.h"
#include "Rayo.h"
#include "Objeto.h"
#include "Luz.h"
#include <vector>
using namespace std;
using namespace cimg_library;
typedef unsigned char BYTE;

const int DEPTH_MAX = 5;

class Camara {
    vec3f pos, xe, ye, ze;
    float w, h;
    float a, b, f, fov;

    CImg<BYTE> *pImg;
    vector<Objeto*> objetos;
    Luz luz;

public:
    Camara() {}
    void calcularVectores(vec3f pos, vec3f center, vec3f up){
        this->pos = pos;
        ze = pos - center;
        ze.normalize();
        xe = up.productoCruz(ze);
        xe.normalize();
        ye = ze.productoCruz(xe);
        cout << "\npos: " << pos;
        cout << "\nxe: " << xe;
        cout << "\nye: " << ye;
        cout << "\nze: " << ze;
    }
    void inicializar(int _w, int _h, float fov, float _near) {
        f = _near;
        w = _w;
        h = _h;
        a = 2 * f * tan(fov * M_PI/360);
        b = w / h * a;
        cout << "\na:" << a;
        cout << "\nb:" << b;
    }
    void setObjetos(vector<Objeto*> _objetos){
      objetos = _objetos;
    }
    void Renderizar();

    vec3f CalcularRayo(Rayo rayo, int depth,int max_depth);
};


#endif //RT1_CAMARA_H
