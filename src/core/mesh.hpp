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

    Float area;

    Mesh(const Point &a, const Point &b, const Point &c);
    Mesh(const Point &a, const Point &b, const Point &c,
         const Normal &na, const Normal &nb, const Normal &nc);
    Mesh(const tuple<const Point &, const Point &, const Point &> &p);
    Mesh(const tuple<const Point &, const Point &, const Point &> &p,
         const tuple<const Normal &, const Normal &, const Normal &> &n);

    BBox getBBox() const;
    bool intersect(const Ray &ray, Intersection *is, Float epilson) const;
    void fillIntersection(Intersection *is) const;

    Point uvToPoint(Float u, Float v) const;
    Normal uvToNormal(Float u, Float v) const;

private:
    Float getArea() const;
};

VSRAY_NAMESPACE_END
