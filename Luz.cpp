#include "Luz.h"

Luz::Luz(vec3f _pos, vec3f _color) : pos{_pos}, color{_color} {}

void Luz::set(vec3f _pos, vec3f _color) {
    pos = _pos;
    color = _color;
}
