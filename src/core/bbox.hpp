#pragma once

#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

class BBox {
public:
    Point pmin, pmax;
    BBox():
        pmin(+INFINITY, +INFINITY, +INFINITY),
        pmax(-INFINITY, -INFINITY, -INFINITY) { }
    explicit BBox(const Point &p) : pmin(p), pmax(p) { }
    BBox(const Point &pmin, const Point &pmax) : pmin(pmin), pmax(pmax) { }
    BBox merge(const BBox &rhs) const {
        return BBox(Point(std::min(pmin.x, rhs.pmin.x),
                          std::min(pmin.y, rhs.pmin.y),
                          std::min(pmin.z, rhs.pmin.z)),
                    Point(std::max(pmax.x, rhs.pmax.x),
                          std::max(pmax.y, rhs.pmax.y),
                          std::max(pmax.z, rhs.pmax.z)));
    }
    Float area() const {
        Vector diff = pmax - pmin;
        return 2 * (diff.x * diff.y + diff.x * diff.z + diff.y * diff.z);
    }
    Float volumn() const {
        Vector diff = pmax - pmin;
        return diff.x * diff.y * diff.z;
    }
};

VSRAY_NAMESPACE_END
