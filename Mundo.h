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
    cam.calcularVectores(vec3f(5, 7, 27), vec3f(0, 0, 0), vec3f(0, 1, 0));
    cam.inicializar(800, 600, 45, 10);

    vector<Objeto*> objetos;

    /*auto *pCilindro1 = new Cilindro(vec3f(0, 5, 0),
                                          vec3f(0, 0, 0),
                                          2.5,
                                          vec3f(255, 233, 0),
                                          vec3f(10, 230, 30),
                                          1);

    pCilindro1->es_reflexivo = true;
    objetos.push_back(pCilindro1);

    Objeto *pEsfera = new Esfera(vec3f(0, 5, 0), 0.1, vec3f(250, 191, 0), vec3f(0.9, 0.5, 0.2), 4);pEsfera->es_reflexivo = true;objetos.push_back(pEsfera);
    Objeto *pEsfera2 = new Esfera(vec3f(0.1, 5.1, 0.1), 0.1, vec3f(0, 0, 0), vec3f(1, 0.6, 0.3), 3);pEsfera2->es_reflexivo = true;objetos.push_back(pEsfera2);

    Objeto *pEsfera3 = new Esfera(vec3f(1, 5, 1), 0.1, vec3f(250, 191, 0), vec3f(0.9, 0.5, 0.2), 4);pEsfera3->es_reflexivo = true;objetos.push_back(pEsfera3);
    Objeto *pEsfera4 = new Esfera(vec3f(1.1, 5.1, 1.1), 0.1, vec3f(0, 0, 0), vec3f(1, 0.6, 0.3), 3);pEsfera4->es_reflexivo = true;objetos.push_back(pEsfera4);

    Objeto *pEsfera5 = new Esfera(vec3f(0.5, 5, 0.5), 0.1, vec3f(250, 191, 0), vec3f(0.9, 0.5, 0.2), 4);pEsfera5->es_reflexivo = true;objetos.push_back(pEsfera5);
    Objeto *pEsfera6 = new Esfera(vec3f(0.6, 5.1, 0.6), 0.1, vec3f(0, 0, 0), vec3f(1, 0.6, 0.3), 3);pEsfera6->es_reflexivo = true;objetos.push_back(pEsfera6);

    Objeto *pEsfera7 = new Esfera(vec3f(-0.5, 5, -0.5), 0.1, vec3f(250, 191, 0), vec3f(0.9, 0.5, 0.2), 4);pEsfera7->es_reflexivo = true;objetos.push_back(pEsfera7);
    Objeto *pEsfera8 = new Esfera(vec3f(-0.6, 5.1, -0.6), 0.1, vec3f(0, 0, 0), vec3f(1, 0.6, 0.3), 3);pEsfera8->es_reflexivo = true;objetos.push_back(pEsfera8);

    Objeto *pEsfera9 = new Esfera(vec3f(-1, 5, -1), 0.1, vec3f(250, 191, 0), vec3f(0.9, 0.5, 0.2), 4);pEsfera9->es_reflexivo = true;objetos.push_back(pEsfera9);
    Objeto *pEsfera10 = new Esfera(vec3f(-1.1, 5.1, -1.1), 0.1, vec3f(0, 0, 0), vec3f(1, 0.6, 0.3), 3);pEsfera10->es_reflexivo = true;objetos.push_back(pEsfera10);

    Objeto *pEsfera11 = new Esfera(vec3f(-1.2, 5, 1.2), 0.1, vec3f(250, 191, 0), vec3f(0.9, 0.5, 0.2), 4);pEsfera11->es_reflexivo = true;objetos.push_back(pEsfera11);
    Objeto *pEsfera12 = new Esfera(vec3f(-1.3, 5.1, 1.3), 0.1, vec3f(0, 0, 0), vec3f(1, 0.6, 0.3), 3);pEsfera12->es_reflexivo = true;objetos.push_back(pEsfera12);
    */
/*
    Caja *pCaja = new Caja(
            vec3f(6.1, 2, 6.1),
            vec3f	(141, 73, 37),
            vec3f(0, 0, 0),
            5);
    pCaja->es_reflexivo = true;
    objetos.push_back(pCaja);
*/
    Plano *pPlano = new Plano(vec3f(0, 0, 0),
                              vec3f(0, 1, 0),
                              vec3f(0.6, 0.6, 1),
                              vec3f(0.9, 0.4, 0), 3);
    objetos.push_back(pPlano);



    ////Matrix de ESFERAS

    for(int kd=0;kd<1;kd++){
        for(int ks=0;ks<1;ks++){
            Objeto *pEspefera14 = new Esfera(vec3f(-10+kd*10,4,-10+ks*10),
                                             4,
                                             vec3f(1,0,0.25),
                                             vec3f(kd*0.1,ks*0.1,0.2),
                                             4);
            pEspefera14->es_reflexivo = true;
            pEspefera14->es_refractivo = true;
            objetos.push_back(pEspefera14);
        }
    }

    Triangulo *pTri1 = new Triangulo(vec3f(10,0,0), vec3f(11,0,8), vec3f(14,7,4), vec3f(0,0,1),
                                     vec3f(0.5,0.5,0), 3);
    objetos.push_back(pTri1);

    cam.setObjetos(objetos);
  };
  void run();
};


#endif //RT1_MUNDO_H
