#include "Caja.h"

Caja::Caja(vec3f _rad, vec3f col, vec3f _kdkskr, float _n) : rad{_rad}, Objeto(col, _kdkskr,_n) {}

bool intersectar(Rayo ray, float &t, vec3f &c, vec3f &normal) override
{
    vec3f m = 1.0/ray.dir;
    vec3f n = ray.ori*m;
    vec3f k = abs(m)*rad;

    vec3f t1 = (-n) - k;
    vec3f t2 = (-n)  + k;

    float tN = fmax( fmax( t1.x, t1.y ), t1.z );
    float tF = fmin( fmin( t2.x, t2.y ), t2.z );

    if( tN > tF || tF < 0.0) return false;

    vec3f nor = (-sign(ray.dir))*step(t1.yzx(),t1.xyz())*step(t1.zxy(),t1.xyz());

    t = tN;
    normal = nor;
    c = color;

    return true;
}

