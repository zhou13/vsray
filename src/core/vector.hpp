#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Vector {
public:
    union {
        struct {
            real x, y, z;
        };
        real f[3];
    };

    Vector(): x(0), y(0), z(0) { }
    Vector(real x, real y, real z): x(x), y(y), z(z) { assert(!isNaN()); }
    bool isNaN() {
        return isnan(x) || isnan(y) || isnan(z);
    }
    Vector &operator +(const Vector &r) const {
        return Vector(x + r.x, y + r.y, z + r.z);
    }
    Vector &operator +=(const Vector &r) const {
        x += r.x;
        y += r.y;
        z += r.z;
        return *this;
    }
    Vector &operator -(const Vector &r) const {
        return Vector(x + r.x, y + r.y, z + r.z);
    }
    Vector &operator -=(const Vector &r) const {
        x -= r.x;
        y -= r.y;
        z -= r.z;
        return *this;
    }
    Vector &operator -() const {
        return Vector(-x, -y, -z);
    }
    Vector &operator *(real r) const {
        assert(!isnan(r));
        return Vector(x * r, y * r, z * r);
    }
    Vector &operator *=(real r) const {
        assert(!isnan(r));
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }
    Vector &operator /(real r) const {
        assert(r != 0);
        return Vector(x / r, y / r, z / r);
    }
    Vector &operator /=(real r) const {
        assert(r != 0);
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }
    real dot(const Vector &r) {
        return x*r.x + y*r.y + z*r.z;
    }
    real cross(const Vector &r) {
        return Vector(y * r.z - z * r.y,
                      z * r.x - x * r.z,
                      x * r.y - y * r.x);
    }
    real length() {
        return sqrt(x*x + y*y + z*z);
    }
    real length2() {
        return x*x + y*y + z*z;
    }
    Vector norm() {
        return *this / len();
    }
};
inline Vector operator*(float f, const Vector &v) {
    return v*f;
}

VSRAY_NAMESPACE_END
