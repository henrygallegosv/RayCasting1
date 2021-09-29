#include "Cilindro.h"

Cilindro::Cilindro(vec3f _pa, vec3f _pb, float _radio, vec3f _color, vec3f _kdkskr, float _n) : pa{_pa}, pb{_pb}, ra{_radio}, Objeto{_color, _kdkskr, _n} {}

bool Cilindro::intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal) {
    vec3f ro = ray.ori;
    vec3f rd = ray.dir;
    vec3f ca = pb-pa;
    vec3f oc = ro-pa;
    float caca = ca.productoPunto(ca);
    float card = ca.productoPunto(rd);
    float caoc = ca.productoPunto(oc);
    float a = caca - card*card;
    float b = caca * oc.productoPunto(rd) - caoc*card;
    float c = caca * oc.productoPunto(oc) - caoc*caoc - ra*ra*caca;
    float h = b*b - a*c;
    if( h < 0.0 ) return false; //no intersection
    h = sqrt(h);
    t = (-b-h)/a;
    if (t <= 0) return false;
    // body
    float y = caoc + t*card;
    if( y > 0.0 && y < caca ) {
        normal = (oc + rd * t - ca * y / caca) / ra;
        col = color;
        return true;
    }
    // caps
    t = ( ( (y < 0.0) ? 0.0 : caca) - caoc)/card;
    if (t <= 0) return false;
    if ( abs(b + a * t) < h ) {
        normal = ca * sgn(y) / caca;
        col = color;
        return true;
    }
    return false; //no intersection
}
