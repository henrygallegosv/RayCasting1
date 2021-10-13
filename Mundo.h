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
  Mundo(){};
  void run();

  void escenario1();
  void escenario2();
  void escenario3();
};


#endif //RT1_MUNDO_H
