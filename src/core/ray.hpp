#pragma once

#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray {
public:
    Point o;
    Vector d;
    Ray(const Point &o_, const Vector &d_) : o(o_), d(d_) { }
    Point operator ()(Float t) {
        return o + t * d;
    }
};

VSRAY_NAMESPACE_END
