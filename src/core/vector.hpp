#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Vector {
public:
    union {
        struct {
            Float x, y, z;
        };
        Float f[3];
    };

    Vector(): x(0), y(0), z(0) { }
    Vector(Float x, Float y, Float z): x(x), y(y), z(z) { assert(!isNaN()); }
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
    Vector &operator *(Float r) const {
        assert(!isnan(r));
        return Vector(x * r, y * r, z * r);
    }
    Vector &operator *=(Float r) const {
        assert(!isnan(r));
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }
    Vector &operator /(Float r) const {
        assert(r != 0);
        return Vector(x / r, y / r, z / r);
    }
    Vector &operator /=(Float r) const {
        assert(r != 0);
        x *= r;
        y *= r;
        z *= r;
        return *this;
    }
    Float dot(const Vector &r) {
        return x*r.x + y*r.y + z*r.z;
    }
    Float cross(const Vector &r) {
        return Vector(y * r.z - z * r.y,
                      z * r.x - x * r.z,
                      x * r.y - y * r.x);
    }
    Float length() {
        return sqrt(x*x + y*y + z*z);
    }
    Float length2() {
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
