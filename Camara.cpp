//
// Created by henry on 8/09/2021.
//

#include <vector>
#include "Camara.h"
#include "Rayo.h"
#include "Objeto.h"
#include "Luz.h"
using namespace std;

void Camara::Renderizar() {
    /*
    Para cada pixel de la pantalla
        Lanzar un rayo
        Para cada objeto de la escena
            Calcule la intersección del rayo con ese objeto
            Almacene la intersección más próxima

        Si el rayo intercepto algún objeto
            Calcule la contribución de las luces en este punto
            Pinte el pixel con ese color
    */
    Rayo ray;
    ray.ori = pos;
    vec3f dir;

    pImg = new CImg<BYTE>(w, h, 1, 10);
    CImgDisplay dis_img((*pImg), "Imagen RayTracing en Perspectiva desde una Camara Pinhole");

    float t, t_min=100000;
    vec3f color, color_min, normal, normal_min;
    float kd_min;
    vector<Objeto*> objetos;
    Objeto *pEsfera = new Esfera(vec3f(3,3,0),4, vec3f(1,0,0.5));
    Objeto *pEsfera2 = new Esfera(vec3f(0,0,0),2, vec3f(0,0,1));
    Objeto *pEsfera3 = new Esfera(vec3f(6,0,0),2, vec3f(0,0.5,0.5));
    pEsfera->kd = 0.3;
    pEsfera2->kd = 0.3;
    pEsfera3->kd = 0.3;
    objetos.push_back(pEsfera);
    //objetos.push_back(pEsfera2);
    //objetos.push_back(pEsfera3);

    Luz luz(vec3f(-10, 10, 0), vec3f(1,1,1));

    bool intersecto, intersecto_uno;
    for(int x=0;  x < w; x++) {
        for(int y=0; y < h; y++) {
            dir = ze*(-f) + ye*a*(y/h-1/2.) + xe*b*(x/w -1/2.);
            dir.normalize();
            ray.dir = dir;
            //cout << "\ndir: " << dir;
            t_min=100000;
            color_min.set(0,0,0);
            kd_min = 0;
            intersecto_uno = false;
            for (auto &obj : objetos) {
                intersecto = obj->intersectar(ray, t, color, normal);

                if (intersecto && t < t_min) {
                    intersecto_uno = true;
                    //cout << "\nx: " << x << " y: " << y;
                    //cout << " dir: " << dir;
                    //cout << " t: " << t << color;

                    t_min = t;
                    color_min = color;
                    normal_min = normal;
                    kd_min = obj->kd;
                }
            }
            if (intersecto_uno) {
                vec3f luz_ambiente = luz.color * 0.1;
                //color_min.normalize();

                // normal vec_luz
                vec3f pi = ray.punto_interseccion(t_min);
                vec3f L = luz.pos - pi;
                L.normalize();

                float factor_difuso = normal_min.productoPunto(L);
                vec3f luz_difusa(0,0,0);
                if (factor_difuso > 0) {
                   luz_difusa = luz.color * kd_min * factor_difuso;
                }
                color_min *= (luz_ambiente + luz_difusa);
                color_min.max_to_one();
                cout << "\nx: " << x << " y: " << y <<" color: " << color_min << " fd: "<< factor_difuso << " L: " << L;
            }

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