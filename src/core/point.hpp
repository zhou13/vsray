#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Point {
public:
    union {
        struct {
            real x, y, z;
        };
        real f[3];
    };

    Point(): x(0), y(0), z(0) { }
    Point(real x, real y, real z): x(x), y(y), z(z) { assert(!isNaN()); }
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
    real distance(const Point &r) const {
        return sqrt(x*x + y*y + z*z);
    }
    real distance2(const Point &r) const {
        return sqrt(x*x + y*y + z*z);
    }
};

VSRAY_NAMESPACE_END
