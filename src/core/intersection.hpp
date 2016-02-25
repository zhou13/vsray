#pragma once

#include "core/vsray.hpp"
#include "core/shape.hpp"
#include "core/geometry.hpp"
#include "core/spectrum.hpp"
#include "core/material.hpp"
#include "core/transform.hpp"

VSRAY_NAMESPACE_BEGIN

class Mesh;
class Ray;
class Shape;
class BSDF;

class Intersection {
public:
    real u, v;
    real mapU, mapV;
    real t, epsilon;

    Point p;
    Vector ta;
    Normal nn, sn;

    const Ray *ray;
    const Shape *shape;
    const Material *material;
    const Transform *transform;

    shared_ptr<BSDF> bsdf;

    Spectrum radiance;

    Intersection() :
        u(0), v(0), 
        ray(nullptr),
        shape(nullptr),
        material(nullptr),
        transform(nullptr),
        radiance(0.f) { }

    void fillIntersection() {
        assert(shape);
        shape->fillIntersection(this);
        if (material)
            bsdf = material->getBSDF(*this);
        if (transform) {
            p = (*transform)(p);
            ta = (*transform)(sn);
            nn = (*transform)(nn);
            sn = (*transform)(sn);
        }
    }
};

VSRAY_NAMESPACE_END
