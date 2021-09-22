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
    float kd_min, ks_min, n_min;
    vector<Objeto*> objetos;
    Objeto *pEsfera = new Esfera(vec3f(3,3,0),4, vec3f(1,0,0.5));
    Objeto *pEsfera2 = new Esfera(vec3f(0,0,0),2, vec3f(0,0,1));
    Objeto *pEsfera3 = new Esfera(vec3f(8,0,0),3, vec3f(0,0.5,0.5));
    pEsfera->kd = 0.9;
    pEsfera2->kd = 0.7;
    pEsfera3->kd = 0.3;
    pEsfera->ks = 0.5;
    pEsfera->n = 4;
    pEsfera2->ks = 0.4;
    pEsfera2->n = 3;
    pEsfera3->ks = 0.3;
    pEsfera3->n = 3;
    objetos.push_back(pEsfera);
    objetos.push_back(pEsfera2);
    objetos.push_back(pEsfera3);
    //Cilindro *pCilindro1 = new Cilindro(vec3f(-5,0,3), 0., 2., 3., vec3f(1.,0.8,0));
    Cilindro *pCilindro1 = new Cilindro(vec3f(-5,0,-3),
                                        vec3f(5, 3, -3), 3,
                                        vec3f(1.0,0.8,0.0));
    pCilindro1->kd = 0.8;
    pCilindro1->ks = 0.4;
    pCilindro1->n = 3;
    objetos.push_back(pCilindro1);

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
                    ks_min = obj->ks;
                    n_min = obj->n;
                }
            }
            if (intersecto_uno) {
                vec3f luz_ambiente = luz.color * 0.1;
                //color_min.normalize();

                // normal vec_luz
                vec3f pi = ray.punto_interseccion(t_min);
                vec3f L = luz.pos - pi;
                L.normalize();

                Rayo rayo_sombra;
                rayo_sombra.ori = pi + L*0.01;
                rayo_sombra.dir = L;

                float factor_sombra = 1;
                /*for (auto &obj : objetos) {
                    intersecto = obj->intersectar(rayo_sombra, t, color, normal);
                    if (intersecto) {
                        factor_sombra = 0;
                        break;
                    }
                }*/

                if (factor_sombra) {
                    float factor_difuso = normal_min.productoPunto(L);
                    vec3f luz_difusa(0, 0, 0);
                    if (factor_difuso > 0) {
                        luz_difusa = luz.color * kd_min * factor_difuso;
                    }

                    // luz especular
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


                //cout << "\nx: " << x << " y: " << y <<" color: " << color_min <<
                //" fd: "<< factor_difuso << " L: " << L <<
                //" fe: " << factor_especular;
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