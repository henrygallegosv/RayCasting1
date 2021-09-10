//
// Created by henry on 8/09/2021.
//

#include <vector>
#include "Camara.h"
#include "Rayo.h"
#include "Objeto.h"
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

    pImg = new CImg<BYTE>(w, h, 1, 3);
    CImgDisplay dis_img((*pImg), "Imagen RayTracing en Perspectiva desde una Camara Pinhole");

    int t, t_min=100000;
    vec3f color, color_min;
    vector<Objeto*> objetos;
    Objeto *pEsfera = new Esfera(vec3f(2,2,0),4, vec3f(255,0,128));
    objetos.push_back(pEsfera);

    for(int x=0;  x < w; x++) {
        for(int y=0; y < h; y++) {
            dir = ze*(-f) + ye*a*(y/h-1/2.) + xe*b*(x/w -1/2.);
            dir.normalize();
            ray.dir = dir;
            //cout << "\ndir: " << dir;
            t_min=100000;
            color_min.set(0,0,0);
            for (auto &obj : objetos) {
                bool intersecto = obj->intersectar(ray, t, color);

                if (intersecto && t < t_min) {
                    //cout << "\ndir: " << dir;
                    //cout << " t: " << t << color;
                    t_min = t;
                    color_min = color;
                }
            }

            (*pImg)(x,y,0) = (BYTE)(color_min.x);
            (*pImg)(x,y,1) = (BYTE)(color_min.y);
            (*pImg)(x,y,2) = (BYTE)(color_min.z);
            dis_img.render((*pImg));
            dis_img.paint();

        }
    }
    while (!dis_img.is_closed()) {
        dis_img.wait();
    }

}