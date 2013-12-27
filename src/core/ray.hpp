#pragma once

#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray {
public:
    Point o;
    Vector d;
    mutable Float maxT;

    Ray(): maxT(INFINITY) { }
    Ray(const Point &o, const Vector &d): o(o), d(d), maxT(INFINITY) { }
    Point operator ()(Float t) {
        return o + t * d;
    }
    string toString() {
        return "[" + o.toString() + "] to " + d.toString();
    }
};

VSRAY_NAMESPACE_END
