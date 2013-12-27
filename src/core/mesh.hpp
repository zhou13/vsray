#pragma once

#include "core/bbox.hpp"
#include "core/geometry.hpp"
#include "core/intersection.hpp"
#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;

class Mesh {
public:
    const Point a, b, c;
    const Normal na, nb, nc;
    bool nn;

    Normal n;

    Mesh(const Point &a, const Point &b, const Point &c);
    Mesh(const Point &a, const Point &b, const Point &c,
         const Normal &na, const Normal &nb, const Normal &nc);
    BBox getBBox();
    bool intersect(const Ray &ray, Intersection *is);
    void fillIntersection(Intersection *is);

    Point uvToPoint(Float u, Float v);
    Normal uvToNormal(Float u, Float v);
    Float area();
};

VSRAY_NAMESPACE_END
