#include <iostream>
#include "Camara.h"

int main() {
    Camara cam;
    cam.calcularVectores(vec3f(0,5,20), vec3f(0,0,0), vec3f(0,1,0));
    cam.inicializar(800, 600, 60, 10);
    cam.Renderizar();
    return 0;
}
