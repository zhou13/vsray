#pragma once

#include "core/vsray.hpp"
#include "core/geometry.hpp"
#include "core/bbox.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Mesh;
class Ray;
class Shape;
class BSDF;

class Intersection {
public:
    Float u, v;
    Float t;
    Point p;

    Normal nn, sn;

    const Ray *ray;
    const Mesh *mesh;
    shared_ptr<BSDF> bsdf;
    Spectrum radiance;

    Intersection() : u(0), v(0), ray(nullptr), mesh(nullptr), radiance(0.f) { }
};

VSRAY_NAMESPACE_END
