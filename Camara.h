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
    void calcularVectores(vec3f pos, vec3f center, vec3f up);
    void inicializar(int _w, int _h, float fov, float _near);
    void setObjetos(vector<Objeto*> _objetos);
    void Renderizar();
    vec3f CalcularRayo(Rayo rayo, int depth,int max_depth);
};


#endif //RT1_CAMARA_H
