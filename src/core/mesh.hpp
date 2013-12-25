#pragma once

#include "core/vsray.hpp"
#include "core/geometry.hpp"
#include "core/bbox.hpp"


VSRAY_NAMESPACE_BEGIN

class Ray;
class Intersection;

class Mesh {
public:
    Point a, b, c;
    Normal n;
    Normal na, nb, nc;

    Mesh() { }
    Mesh(const Point &a, const Point &b, const Point &c) : a(a), b(b), c(c) {
        n = Normal((b-a).cross(c-b).normalize());
    }
    Mesh(const Point &a, const Point &b, const Point &c,
         const Normal &na, const Normal &nb, const Normal &nc) :
        a(a), b(b), c(c), na(na), nb(nb), nc(nc)
    {
        n = Normal((b-a).cross(c-b).normalize());
    }

    BBox getBBox();
    bool intersect(const Ray &ray, Intersection *is);
    Point uvToPoint(Float u, Float v);
};

VSRAY_NAMESPACE_END
