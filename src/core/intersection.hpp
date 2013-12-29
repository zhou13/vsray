#pragma once

#include "core/vsray.hpp"
#include "core/shape.hpp"
#include "core/geometry.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Mesh;
class Ray;
class Shape;
class BSDF;

class Intersection {
public:
    real u, v;
    real t, epsilon;
    Point p;

    Normal nn, sn, ta;

    const Ray *ray;
    const Shape *shape;
    shared_ptr<BSDF> bsdf;
    Spectrum radiance;

    Intersection() :
        u(0), v(0), ray(nullptr), shape(nullptr), radiance(0.f) { }
    void fillIntersection() {
        assert(shape);
        shape->fillIntersection(this);
    }
};

VSRAY_NAMESPACE_END
