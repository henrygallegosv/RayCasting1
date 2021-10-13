#include <vector>
#include "Camara.h"
#include <algorithm>

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

    luz.set(vec3f(-10, 10, 20), vec3f(1,1,1));

    Luz *pLuz1 = new Luz;
    pLuz1->set(vec3f(-10, 10, 10), vec3f(1,1,1));
    Luz *pLuz2 = new Luz;
    pLuz2->set(vec3f(20, 10, 10), vec3f(1,1,1));

    vec3f color1(1, .9, 0), pos1(0,4,0);
    Luz *pLuzEsfera1 = new Luz;
    pLuzEsfera1->set(pos1, color1);

    //luces.push_back(pLuz2);
    luces.push_back(pLuz1);
    luces.push_back(pLuzEsfera1);

    bool intersecto, intersecto_uno;
    Objeto *pObj;
    for(int x=0;  x < w; x++) {
        for(int y=0; y < h; y++) {
            cout << "(" << x << "," << y << ") ";
            ray.dir = ze*(-f) + ye*a*(y/h-1/2.) + xe*b*(x/w -1/2.);
            ray.dir.normalize();
            vec3f color_min = CalcularRayo(ray,1,5);

            (*pImg)(x,h-1-y,0) = (BYTE)(color_min.x * 255);
            (*pImg)(x,h-1-y,1) = (BYTE)(color_min.y * 255);
            (*pImg)(x,h-1-y,2) = (BYTE)(color_min.z * 255);
        }
        dis_img.render((*pImg));
        dis_img.paint();
    }
    dis_img.render((*pImg));
    dis_img.paint();

    while (!dis_img.is_closed()) {
        dis_img.wait();
    }

}
bool Camara::CalcularInterseccion(Rayo rayo, ColorInfo &colorinfo) {
    float t, t_min=100000;
    vec3f color;
    vec3f normal;
    bool intersecto, intersecto_uno = false;
    for (auto &obj : objetos) {
        intersecto = obj->intersectar(rayo, t, color, normal);

        if (intersecto && t < t_min) {
            intersecto_uno = true;

            t_min = t;
            colorinfo.color = color;
            colorinfo.normal = normal;
            //kd_min = obj->kdkskr.x;
            //ks_min = obj->kdkskr.y;
            //n_min = obj->n;
            colorinfo.pObj = obj;
        }
    }
    return intersecto_uno;
}


vec3f Camara::CalcularRayo(Rayo rayo, int depth,int max_depth){
    if(depth > max_depth) return vec3f(0,0,0);
    float t, t_min=100000;
    vec3f color, color_min; color_min.set(0,0,0);
    vec3f normal, normal_min;
    float ks_min, n_min, kd_min = 0;
    bool intersecto, intersecto_uno = false;
    Objeto *pObj, *pObjSombra;
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
    //ColorInfo colorinfo;
    //intersecto_uno = CalcularInterseccion(rayo, colorinfo);
    //pObj   = colorinfo.pObj;
    if (intersecto_uno && pObj->esFuenteLuz) {
        return color_min;
    }

    if (intersecto_uno) {
        /*color_min = colorinfo.color;
        normal_min = colorinfo.normal;
        kd_min = colorinfo.pObj->kdkskr.x;
        ks_min = colorinfo.pObj->kdkskr.y;
        n_min  = colorinfo.pObj->n;*/

        vec3f color_res;

        for (auto &pLuz : luces) {
            vec3f color_luz;
            vec3f luz_ambiente = luz.color * 0.1;

            // normal vec_luz
            vec3f pi = rayo.punto_interseccion(t_min);
            vec3f L = pLuz->pos - pi;
            L.normalize();

            Rayo rayo_sombra;
            rayo_sombra.ori = pi + L*0.0001;
            rayo_sombra.dir = L;

            float en_sombra = false;
            for (auto &obj : objetos) {
                intersecto = obj->intersectar(rayo_sombra, t, color, normal);
                if (intersecto) {
                    en_sombra = true;
                    break;
                }
            }
            /*ColorInfo colorinfo_sombra;
            intersecto_uno = CalcularInterseccion(rayo_sombra, colorinfo_sombra);
            pObjSombra   = colorinfo_sombra.pObj;
            if (intersecto_uno && pObjSombra->esFuenteLuz) {
                color_luz = luz_ambiente + colorinfo_sombra.color;
            }*/
            /*else if (intersecto_uno && pObjSombra->es_refractivo) {
                vec3f color_sombra = CalcularRayo(rayo_sombra, depth + 1, max_depth);
                color_luz = luz_ambiente + color_sombra;
            }*/
            if ( !en_sombra ) {
                float factor_difuso = normal_min.productoPunto(L);
                vec3f luz_difusa(0, 0, 0);
                if (factor_difuso > 0) {
                    luz_difusa = pLuz->color * kd_min * factor_difuso;
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
                    luz_especular = pLuz->color * ks_min * factor_especular;
                }

                color_luz = luz_ambiente + luz_difusa + luz_especular;
            } else {
                color_luz = luz_ambiente;
            }
            color_luz.max_to_one();

            // Lanzar los rayos secundarios
            // Reflexivo
            vec3f color_refractivo;
            float kr = pObj->kdkskr.z, kt=0;
            if(pObj->es_refractivo) {
                vec3f dirRefr = CalcularRefraccion(rayo.dir, normal_min, 1.5, kr);
                dirRefr.normalize();
                kt = 1 - kr;
                if (kt > 0) {
                    Rayo rayo_refractivo;
                    rayo_refractivo.dir = dirRefr;
                    rayo_refractivo.ori = pi + dirRefr*0.0001;
                    color_refractivo = CalcularRayo(rayo_refractivo, depth+1, max_depth);
                    color_refractivo = color_refractivo * kt;
                }
                if (kr > 0) {
                    normal_min = -normal_min;
                }
            }

            vec3f color_reflexivo;
            if (pObj->es_reflexivo && depth < DEPTH_MAX) {
                Rayo rayo_reflexivo;
                vec3f vec_rayo = -rayo.dir;
                rayo_reflexivo.dir = normal_min * 2. * (vec_rayo.productoPunto(normal_min)) - vec_rayo;
                rayo_reflexivo.ori = pi + rayo_reflexivo.dir*0.0001;
                color_reflexivo = CalcularRayo(rayo_reflexivo, depth + 1,max_depth);
                color_reflexivo = color_reflexivo * kr;
            }
            color_luz = color_luz + color_reflexivo + color_refractivo;
            //color_luz.max_to_one();

            // path tracing
            // lanzar rayos
            // acumular el color
            vec3f color_path_tracing, color_res_pt;
            Rayo rayo_pt;
            for (int i=0; i<5; i++) {
                vec3f ndir(normal_min.x + (rand()%100/100),
                           normal_min.y + (rand()%100/100),
                           normal_min.z + (rand()%100/100));
                ndir.normalize();
                rayo_pt.dir = ndir;
                rayo_pt.ori = pi + ndir*0.0001;
                color_res_pt = CalcularRayo(rayo_pt, depth + 1,max_depth);

                color_path_tracing = color_path_tracing + color_res_pt;
            }
            color_path_tracing.max_to_one();

            color_res = color_res + color_luz + color_path_tracing;
        }
        color_res.max_to_one();
        //color_res = color_res / luces.size();

        color_min *= color_res;
        color_min.max_to_one();
        return color_min;
    }
    return vec3f(0,0,0);
}

vec3f Camara::CalcularRefraccion(vec3f &I, vec3f &normal, float n, float &kr){
  vec3f T;
  float cosi = clip(-1, 1, I.productoPunto(normal));
  float etai = 1, etat = n;
  if (cosi > 0) {
    std::swap(etai, etat);
  }
  // Compute sini using Snell's law
  float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
  // Total internal reflection
  if (sint >= 1) {
    kr = 1;
  }
  else {
    float cost = sqrtf(std::max(0.f, 1 - sint * sint));
    cosi = fabsf(cosi);
    float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
    float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
    kr = (Rs * Rs + Rp * Rp) / 2;
    //float c1 = normal.productoPunto(I);
    // float c2 = sqrt(1-pow(etai/etat, 2) *(1-c1*c1));
    T = I*etai + normal * (etai * cosi - cost);
  }
  return T;
}
