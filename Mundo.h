//
// Created by henry on 8/09/2021.
//

#ifndef RT1_MUNDO_H
#define RT1_MUNDO_H
#include "./Camara.h"

class Mundo {
  Camara cam;
  Mundo(){
    cam.calcularVectores(vec3f(-4, 10, 20), vec3f(0, 0, 0), vec3f(0, 1, 0));
    cam.inicializar(800, 600, 45, 10);
    cam.Renderizar();
  }
};


#endif //RT1_MUNDO_H
