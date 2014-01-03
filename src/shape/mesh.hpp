#pragma once

#include "core/bbox.hpp"
#include "core/geometry.hpp"
#include "core/intersection.hpp"
#include "core/vsray.hpp"
#include "core/shape.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;

class Mesh : public Shape {
public:
    const Point a, b, c;
    const Normal na, nb, nc;
    const Vector e1, e2;

    static int indexCnt;
    int index;

    bool nn;
    Normal n;

    real area;

    Mesh(const Point &a, const Point &b, const Point &c);
    Mesh(const Point &a, const Point &b, const Point &c,
         const Normal &na, const Normal &nb, const Normal &nc);
    Mesh(const tuple<const Point &, const Point &, const Point &> &p);
    Mesh(const tuple<const Point &, const Point &, const Point &> &p,
         const tuple<const Normal &, const Normal &, const Normal &> &n);

    virtual BBox getBBox() const;
    virtual bool intersect(const Ray &ray, Intersection *is, real epilson) const;
    virtual void fillIntersection(Intersection *is) const;

    Point uvToPoint(real u, real v) const;
    Normal uvToNormal(real u, real v) const;
    string toString() const;

private:
    real getArea() const;
};

VSRAY_NAMESPACE_END
