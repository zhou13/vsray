#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Point {
public:
    union {
        struct {
            Float x, y, z;
        };
        Float f[3];
    };

    Point(): x(0), y(0), z(0) { }
    Point(Float x, Float y, Float z): x(x), y(y), z(z) { assert(!isNaN()); }
    bool isNaN() {
        return isnan(x) || isnan(y) || isnan(z);
    }
    Point &operator +(const Vector &r) const {
        return Point(x + r.x, y + r.y, z + r.z);
    }
    Point &operator +=(const Vector &r) const {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
    }
    Point &operator -(const Vector &r) const {
        return Point(x + r.x, y + r.y, z + r.z);
    }
    Point &operator -=(const Point &r) const {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        return *this;
    }
    Vector &operator -(const Point &r) const {
        return Vector(x + r.x, y + r.y, z + r.z);
    }
    Float distance(const Point &r) const {
        return sqrt(x*x + y*y + z*z);
    }
    Float distance2(const Point &r) const {
        return sqrt(x*x + y*y + z*z);
    }
};

VSRAY_NAMESPACE_END
