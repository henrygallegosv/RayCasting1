//
// Created by henry on 9/09/2021.
//

#ifndef RT1_OBJETO_H
#define RT1_OBJETO_H

#include "vector.h"
#include "Rayo.h"

class Objeto {
public:
vec3f color;
vec3f kdkskr;
bool es_reflexivo, es_refractivo;
float nu, n;
Objeto(vec3f col, vec3f _kdkskr, float _n) : n{_n},color{col}, kdkskr{_kdkskr}
{
  //kd = ks = 0;
  es_reflexivo = es_refractivo = false;
}

//virtual bool intersectar(Rayo ray, int &t, vec3f &c)=0;
virtual bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &normal)=0;
};

class Esfera : public Objeto {
public:
    vec3f centro;
    float radio;

    Esfera(vec3f cen, float r, vec3f col, vec3f _kdkskr, float _n) : centro{cen}, radio{r}, Objeto(col, _kdkskr,_n) {}
    bool intersectar(Rayo ray, float &t, vec3f &col, vec3f &normal) {
        auto _a = ray.dir.productoPunto(ray.dir);
        auto _b = 2*ray.dir.productoPunto(ray.ori-centro);
        auto _c = (ray.ori-centro).productoPunto(ray.ori-centro)-radio*radio;
        auto D = _b*_b-4*_a*_c;
        if(D <= 0) {return false;}
        float t1 = (-_b + sqrt(D))/2*_a;
        float t2 = (-_b - sqrt(D))/2*_a;
        t = std::min(t1, t2);
        if(t <= 0) {return false;}
        col = color;
        vec3f pi = ray.punto_interseccion(t);
        normal = pi - centro;
        normal.normalize();

        return true;

    }
};

class Caja : public Objeto {
public:
    vec3f rad;
    Caja(vec3f _rad, vec3f col, vec3f _kdkskr, float _n) : rad{_rad}, Objeto(col, _kdkskr,_n) {}

    bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &normal)
    //vec4 iBox( in vec3 ro, in vec3 rd, in mat4 txx, in mat4 txi, in vec3 rad )
    {
        // convert from ray to box space
        //vec3 rdd = (txx*vec4(rd,0.0)).xyz;
        //vec3 roo = (txx*vec4(ro,1.0)).xyz;

        // ray-box intersection in box space
        vec3f m = 1.0/ray.dir;
        vec3f n = ray.ori*m;
        vec3f k = abs(m)*rad;

        vec3f t1 = (-n) - k;
        vec3f t2 = (-n)  + k;

        float tN = fmax( fmax( t1.x, t1.y ), t1.z );
        float tF = fmin( fmin( t2.x, t2.y ), t2.z );

        if( tN > tF || tF < 0.0) return false;

        vec3f nor = (-sign(ray.dir))*step(t1.yzx(),t1.xyz())*step(t1.zxy(),t1.xyz());

        // convert to ray space
        //nor = (txi * vec4(nor,0.0)).xyz;

        t = tN;
        normal = nor;
        c = color;
        //return vec4( tN, nor );
        return true;
    }
};

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

class Plano : public Objeto {
public:
    vec3f punto, normal;

    Plano(vec3f _punto, vec3f _normal, vec3f _color, vec3f _kdkskr, float _n) : punto{_punto}, normal{_normal}, Objeto(_color, _kdkskr,_n)
    {
      normal.normalize();
    }

    bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &_normal) {
        t = normal.productoPunto(punto-ray.ori)/ normal.productoPunto(ray.dir);
        if ( t > 0.0001 ) {
            _normal = normal;
            c = color;
            return true;
        }
        return false;
    }
};


#endif //RT1_OBJETO_H
