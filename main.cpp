#include <iostream>
#include "Camara.h"

int main() {
    Camara cam;
    cam.calcularVectores(vec3f(0,5,20), vec3f(0,0,0), vec3f(0,1,0));
    cam.inicializar(200, 100, 90, 2);
    cam.Renderizar();
    return 0;
}
