#pragma once

#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray {
public:
    Point o;
    Vector d;
    mutable real maxT;

    Ray(): maxT(INFINITY) { }
    Ray(const Point &o, const Vector &d, real maxT = INFINITY) :
        o(o), d(d), maxT(maxT) { }
    Point operator ()(real t) {
        return o + t * d;
    }
    string toString() {
        return "[" + o.toString() + "] to " + d.toString();
    }
};

VSRAY_NAMESPACE_END
