#include <vector>
#include "Camara.h"

using namespace std;

void Camara::calcularVectores(vec3f pos, vec3f center, vec3f up) {
    this->pos = pos;
    ze = pos - center;
    ze.normalize();
    xe = up.productoCruz(ze);
    xe.normalize();
    ye = ze.productoCruz(xe);
    cout << "\npos: " << pos;
    cout << "\nxe: " << xe;
    cout << "\nye: " << ye;
    cout << "\nze: " << ze;
}

void Camara::inicializar(int _w, int _h, float fov, float _near) {
    f = _near;
    w = _w;
    h = _h;
    a = 2 * f * tan(fov * M_PI/360);
    b = w / h * a;
    cout << "\na:" << a;
    cout << "\nb:" << b;
}

void Camara::setObjetos(vector<Objeto *> _objetos) {
    objetos = _objetos;
}

void Camara::Renderizar() {
    Rayo ray;
    ray.ori = pos;

    pImg = new CImg<BYTE>(w, h, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayTracing en Perspectiva desde una Camara Pinhole");

    vec3f color_min;

    luz.set(vec3f(-10, 10, 0), vec3f(1,1,1));

    bool intersecto, intersecto_uno;
    Objeto *pObj;
    for(int x=0;  x < w; x++) {
        for(int y=0; y < h; y++) {
            ray.dir = ze*(-f) + ye*a*(y/h-1/2.) + xe*b*(x/w -1/2.);
            ray.dir.normalize();
            vec3f color_min = CalcularRayo(ray,1,5);

            (*pImg)(x,h-1-y,0) = (BYTE)(color_min.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color_min.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color_min.z * 255);
            //dis_img.render((*pImg));
            //dis_img.paint();

        }
    }
    dis_img.render((*pImg));
    dis_img.paint();
    while (!dis_img.is_closed()) {
        dis_img.wait();
    }

}

vec3f Camara::CalcularRayo(Rayo rayo, int depth,int max_depth){
    if(depth > max_depth) return vec3f(0,0,0);
    float t, t_min=100000;
    vec3f color, color_min; color_min.set(0,0,0);
    vec3f normal, normal_min;
    float ks_min, n_min, kd_min = 0;
    bool intersecto, intersecto_uno = false;
    Objeto *pObj;
    for (auto &obj : objetos) {
        intersecto = obj->intersectar(rayo, t, color, normal);

        if (intersecto && t < t_min) {
            intersecto_uno = true;

            t_min = t;
            color_min = color;
            normal_min = normal;
            kd_min = obj->kdkskr.x;
            ks_min = obj->kdkskr.y;
            n_min = obj->n;
            pObj = obj;
        }
    }
    if (intersecto_uno) {
        vec3f luz_ambiente = luz.color * 0.1;
        //color_min.normalize();

        // normal vec_luz
        vec3f pi = rayo.punto_interseccion(t_min);
        vec3f L = luz.pos - pi;
        L.normalize();

        Rayo rayo_sombra;
        rayo_sombra.ori = pi + L*0.0001;
        rayo_sombra.dir = L;

        float factor_sombra = 1;
        for (auto &obj : objetos) {
            intersecto = obj->intersectar(rayo_sombra, t, color, normal);
            if (intersecto) {
                factor_sombra = 0;
                break;
            }
        }
        if (factor_sombra) {
            float factor_difuso = normal_min.productoPunto(L);
            vec3f luz_difusa(0, 0, 0);
            if (factor_difuso > 0) {
                luz_difusa = luz.color * kd_min * factor_difuso;
            }

            // luz especular
            vec3f dir = rayo.dir;
            vec3f V(-dir.x, -dir.y, -dir.z); // vector hacia el observador
            vec3f r = normal_min * 2. * (L.productoPunto(normal_min)) - L;
            r.normalize();

            float factor_especular = r.productoPunto(V);
            vec3f luz_especular(0, 0, 0);
            if (factor_especular > 0.0) {
                factor_especular = pow(factor_especular, n_min);
                luz_especular = luz.color * ks_min * factor_especular;
            }

            color_min *= (luz_ambiente + luz_difusa + luz_especular);
            color_min.max_to_one();
        } else {
            color_min *= luz_ambiente;
            color_min.max_to_one();
        }

        // Lanzar los rayos secundarios
        // Reflexivo
        vec3f color_reflexivo;
        if (pObj->es_reflexivo && depth < DEPTH_MAX) {
            Rayo rayo_reflexivo;
            rayo_reflexivo.ori = pi + L*0.0001;
            vec3f vec_rayo = -rayo.dir;
            rayo_reflexivo.dir = normal_min * 2. * (vec_rayo.productoPunto(normal_min)) - vec_rayo;
            color_reflexivo = CalcularRayo(rayo_reflexivo, depth + 1,max_depth);

            color_min = color_min + color_reflexivo * pObj->kdkskr.z;
            color_min.max_to_one();
        }


        return color_min;
    }
    return vec3f(0,0,0);
}


