//
// Created by henry on 8/09/2021.
//

#include "vector.h"
std::ostream& operator<<(std::ostream &os, vec3f v){
    os << "[" << v.x << ", " << v.y << "," << v.z << "]";
    return os;
}
