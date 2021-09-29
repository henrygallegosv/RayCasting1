#ifndef RT1_MUNDO_H
#define RT1_MUNDO_H
#include "./Camara.h"
#include "Cilindro.h"
#include "Esfera.h"
#include "Plano.h"
#include "Caja.h"

class Mundo {
  public:
  Camara cam;
  Mundo(){
    std::cout<<"dentro de mundo";
    cam.calcularVectores(vec3f(-4, 10, 20), vec3f(0, 0, 0), vec3f(0, 1, 0));
    cam.inicializar(800, 600, 45, 10);
    vector<Objeto*> objetos;
    Objeto *pEsfera = new Esfera(vec3f(3, 3, 0), 4, vec3f(1, 0, 0.5), vec3f(0.9, 0.5, 0.2), 4);
    Objeto *pEsfera2 = new Esfera(vec3f(0, -5, 5), 2, vec3f(0, 0, 1), vec3f(0.7, 0.4, 0.8), 3);
    Objeto *pEsfera3 = new Esfera(vec3f(8, 0, 0), 3, vec3f(0, 0.5, 0.5), vec3f(0.3, 0.3, 0.5), 3);
    pEsfera->es_reflexivo = true;
    pEsfera2->es_reflexivo = true;
    pEsfera3->es_reflexivo = true;
    objetos.push_back(pEsfera);
    objetos.push_back(pEsfera2);
    objetos.push_back(pEsfera3);

    Cilindro *pCilindro1 = new Cilindro(vec3f(-5, 0, -3),
                                        vec3f(5, 3, -3), 3,
                                        vec3f(1.0, 0.8, 0.0),
                                        vec3f(0.8, 0.4, 0.8), 3);
    pCilindro1->es_reflexivo = true;
    objetos.push_back(pCilindro1);

    /*
    Caja *pCaja = new Caja(vec3f(5, 1, 6), vec3f(0, .8, .9), vec3f(0.6, 0.3, 0.5), 5);
    objetos.push_back(pCaja);
    */

    Plano *pPlano = new Plano(vec3f(0, -5, 0), vec3f(-1, 5, 0), vec3f(1.0, 0.8, 0.8), vec3f(0.9, 0.4, 0.3), 3);
    objetos.push_back(pPlano);

    cam.setObjetos(objetos);
  };
  void run();
};


#endif //RT1_MUNDO_H
