#pragma once
#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Vector;
class Normal;
class Point;

class Vector {
public:
    union {
        struct {
            real x, y, z;
        };
        real f[3];
    };

    Vector() : x(0), y(0), z(0) { }
    Vector(real x, real y, real z) : x(x), y(y), z(z) { assert(!isNaN()); }
    bool isNaN() const {
        return isnan(x) || isnan(y) || isnan(z);
    }
    Vector operator +(const Vector &rhs) const {
        return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    Vector &operator +=(const Vector &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    Vector operator -(const Vector &rhs) const {
        return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    Vector &operator -=(const Vector &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    Vector operator -() const {
        return Vector(-x, -y, -z);
    }
    Vector operator *(real rhs) const {
        assert(!isnan(rhs));
        return Vector(x * rhs, y * rhs, z * rhs);
    }
    Vector &operator *=(real rhs) {
        assert(!isnan(rhs));
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }
    Vector operator /(real rhs) const {
        assert(rhs != 0);
        real inv = 1.f / rhs;
        return Vector(x * inv, y * inv, z * inv);
    }
    Vector &operator /=(real rhs) {
        assert(rhs != 0);
        real inv = 1.f / rhs;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    bool operator ==(const Vector &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    real operator [](uint32_t i) const {
        return f[i];
    }
    real dot(const Vector &rhs) const {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }
    Vector cross(const Vector &rhs) const {
        return Vector(y * rhs.z - z * rhs.y,
                      z * rhs.x - x * rhs.z,
                      x * rhs.y - y * rhs.x);
    }
    real length() const {
        return sqrt(x*x + y*y + z*z);
    }
    real length2() const {
        return x*x + y*y + z*z;
    }
    Vector normalize() const {
        return *this / length();
    }
    friend Vector operator*(float f, const Vector &v) {
        return v*f;
    }
    string toString() {
        return ("(" +
                lexical_cast<string>(x) + ", " +
                lexical_cast<string>(y) + ", " +
                lexical_cast<string>(z) + ")");
    }
};


class Normal {
public:
    union {
        struct {
            real x, y, z;
        };
        real f[3];
    };

    Normal() : x(0), y(0), z(0) { }
    Normal(real x, real y, real z) : x(x), y(y), z(z) { assert(!isNaN()); }
    explicit Normal(const Vector &v) : x(v.x), y(v.y), z(v.z) { }
    operator Vector() const {
        return Vector(x, y, z);
    }
    bool isNaN() const {
        return isnan(x) || isnan(y) || isnan(z);
    }
    Normal operator +(const Normal &rhs) const {
        return Normal(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    Normal &operator +=(const Normal &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    Normal operator -(const Normal &rhs) const {
        return Normal(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    Normal &operator -=(const Normal &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    Normal operator -() const {
        return Normal(-x, -y, -z);
    }
    Normal operator *(real rhs) const {
        assert(!isnan(rhs));
        return Normal(x * rhs, y * rhs, z * rhs);
    }
    Normal &operator *=(real rhs) {
        assert(!isnan(rhs));
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }
    Normal operator /(real rhs) const {
        assert(rhs != 0);
        real inv = 1.f / rhs;
        return Normal(x * inv, y * inv, z * inv);
    }
    Normal &operator /=(real rhs) {
        assert(rhs != 0);
        real inv = 1.f / rhs;
        x *= inv;
        y *= inv;
        z *= inv;
        return *this;
    }
    bool operator ==(const Normal &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
    real operator [](uint32_t i) const {
        return f[i];
    }
    real dot(const Normal &rhs) const {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }
    real dot(const Vector &rhs) const {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }
    real length() const {
        return sqrt(x*x + y*y + z*z);
    }
    real length2() const {
        return x*x + y*y + z*z;
    }
    Normal normalize() const {
        return *this / length();
    }
    string toString() {
        return ("(" +
                lexical_cast<string>(x) + ", " +
                lexical_cast<string>(y) + ", " +
                lexical_cast<string>(z) + ")");
    }
};

class Point {
public:
    union {
        struct {
            real x, y, z;
        };
        real f[3];
    };

    Point() : x(0), y(0), z(0) { }
    Point(real x, real y, real z) : x(x), y(y), z(z) { assert(!isNaN()); }
    explicit Point(const Vector &v) : x(v.x), y(v.y), z(v.z) { }
    explicit operator Vector() const {
        return Vector(x, y, z);
    }
    bool isNaN() const {
        return isnan(x) || isnan(y) || isnan(z);
    }
    Point operator +(const Vector &rhs) const {
        return Point(x + rhs.x, y + rhs.y, z + rhs.z);
    }
    Point &operator +=(const Vector &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    Point operator -(const Vector &rhs) const {
        return Point(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    Point &operator -=(const Point &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }
    Vector operator -(const Point &rhs) const {
        return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
    }
    real operator [](uint32_t i) const {
        return f[i];
    }
    real distance(const Point &rhs) const {
        return (*this-rhs).length();
    }
    real distance2(const Point &rhs) const {
        return (*this-rhs).length2();
    }
    string toString() {
        return ("(" +
                lexical_cast<string>(x) + ", " +
                lexical_cast<string>(y) + ", " +
                lexical_cast<string>(z) + ")");
    }
};

VSRAY_NAMESPACE_END
