//
// Created by davla on 28/09/2021.
//

#ifndef RT1_CILINDRO_H
#define RT1_CILINDRO_H

class Cilindro: public Objeto {
public:
    vec3f centro;
    //float yMin, yMax, radio;
    vec3f pa, pb;
    float ra;

    // Cilindro(vec3f cen, float y_min, float y_max, float rad, vec3f _color):
    //centro{cen}, yMin{y_min}, yMax{y_max}, radio{rad}, Objeto(_color) {}
    Cilindro(vec3f _pa, vec3f _pb, float _radio, vec3f _color, vec3f _kdkskr, float _n) : pa{_pa}, pb{_pb}, ra{_radio}, Objeto{_color, _kdkskr, _n} {}

    /*
    bool intersectar1(Rayo ray, float &t, vec3f &col, vec3f &normal) {
        auto _a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
        auto _b = 2 * (ray.dir.x * ray.ori.x + ray.dir.z * ray.ori.z );
        auto _c = ray.ori.x * ray.ori.x + ray.ori.z * ray.ori.z - radio * radio;

        auto D = _b*_b-4*_a*_c;
        if(D <= 0) {return false;}


        float t1 = (-_b + sqrt(D))/2*_a;
        float t2 = (-_b - sqrt(D))/2*_a;
        t = std::min(t1, t2);
        vec3f pi = ray.punto_interseccion(t);
        if (t <= 0 || pi.y < yMin || pi.y > yMax) {
            t = std::max(t1, t2);
            pi = ray.punto_interseccion(t);
            if (pi.y < yMin || pi.y > yMax) {
                return false;
            }
        }
        col = color;
        vec3f cen(centro.x, pi.y ,centro.z);
        normal = pi - cen;
        normal.normalize();

        return true;

    }
     */

    // Capped cylinder
    // cylinder defined by extremes pa and pb, and radious ra
    bool intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal)
    //in vec3 ro, in vec3 rd, in vec3 pa, in vec3 pb, float ra )
    {

        vec3f ro = ray.ori;
        vec3f rd = ray.dir;
        vec3f ca = pb-pa;
        vec3f oc = ro-pa;
        float caca = ca.productoPunto(ca); //dot(ca,ca);
        float card = ca.productoPunto(rd); //dot(ca,rd);
        float caoc = ca.productoPunto(oc); //dot(ca,oc);
        float a = caca - card*card;
        //float b = caca * dot( oc, rd) - caoc*card;
        float b = caca * oc.productoPunto(rd) - caoc*card;
        //float c = caca * dot( oc, oc) - caoc*caoc - ra*ra*caca;
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
};


#endif //RT1_CILINDRO_H
