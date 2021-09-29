//
// Created by davla on 28/09/2021.
//

#ifndef RT1_CAJA_H
#define RT1_CAJA_H

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

#endif //RT1_CAJA_H
