#pragma once

#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray {
public:
    Point o;
    Vector d;
    Ray() { }
    Ray(const Point &o, const Vector &d): o(o), d(d) { }
    Point operator ()(Float t) {
        return o + t * d;
    }
    string toString() {
        return "[" + o.toString() + "] to " + d.toString();
    }
};

VSRAY_NAMESPACE_END
