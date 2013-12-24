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
    Mesh(const Point &a_, const Point &b_, const Point &c_)
        : a(a_), b(b_), c(c_)
    {
        n = (b-a).cross(c-b).normalize();
    }
    Mesh(const Point &a_, const Point &b_, const Point &c_
         const Normal &na, const Normal &nb, const Normal &nb)
        : a(a_), b(b_), c(c_), na(na_), nb(nb_), nc(nc_)
    {
        n = (b-a).cross(c-b).normalize();
    }

    BBox getBBox();
    bool intersect(const Ray &ray, Intersection *is);
    Point uvToPoint(Float u, Float v);
};

VSRAY_NAMESPACE_END
