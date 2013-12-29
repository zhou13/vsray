#pragma once

#include "core/geometry.hpp"
#include "core/ray.hpp"

VSRAY_NAMESPACE_BEGIN

class BBox {
public:
    union {
        struct {
            real x0, y0, z0;
        };
        real v0[3];
    };
    union {
        struct {
            real x1, y1, z1;
        };
        real v1[3];
    };

    inline BBox() :
        x0(+INFINITY), y0(+INFINITY), z0(+INFINITY),
        x1(-INFINITY), y1(-INFINITY), z1(-INFINITY) { }
    inline explicit BBox(const Point &p) :
        x0(p.x), y0(p.y), z0(p.z),
        x1(p.x), y1(p.y), z1(p.z) { }
    inline BBox(real x0, real x1, real y0, real y1, real z0, real z1) :
        x0(x0), y0(y0), z0(z0), x1(x1), y1(y1), z1(z1) { }

    inline BBox merge(const BBox &rhs) const {
        return BBox(
                std::min(x0, rhs.x0),
                std::max(x1, rhs.x1),
                std::min(y0, rhs.y0),
                std::max(y1, rhs.y1),
                std::min(z0, rhs.z0),
                std::max(z1, rhs.z1)
        );
    }
    inline real area() const {
        real dx = x1 - x0;
        real dy = y1 - y0;
        real dz = z1 - z0;
        return 2 * (dx * dy + dy * dz + dz * dx);
    }
    inline bool inrange(real m, real v0, real v1) {
        return v0 <= m && v1 <= m;
    }
    inline bool inside(const Point &p) {
        if (inrange(p.x, x0, x1) &&
            inrange(p.y, y0, y1) &&
            inrange(p.z, z0, z1))
        {
            return true;
        }
        return false;
    }
    inline bool maxExtent()
    {
        real e1 = x1 - x0;
        real e2 = y1 - y0;
        real e3 = z1 - z0;
        if (e1 >= e2 && e1 >= e3)
            return e1;
        if (e2 >= e3)
            return e2;
        return e3;
    }
};

VSRAY_NAMESPACE_END
