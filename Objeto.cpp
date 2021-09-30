#include "Objeto.h"

Objeto::Objeto(vec3f col, vec3f _kdkskr, float _n) : n{_n},color{col}, kdkskr{_kdkskr}
{
    es_reflexivo = es_refractivo = false;

}
