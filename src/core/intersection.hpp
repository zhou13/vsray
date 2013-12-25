#pragma once

#include <core/vsray.hpp>

VSRAY_NAMESPACE_BEGIN

class Mesh;
class Shape;

class Intersection {
public:
    Float u, v;
    Float t;
    Point p;
    Normal nn, sn;

    const Ray *ray;
    const Mesh *mesh;
    const Shape *shape;

    Intersection() :
        u(0), v(0), ray(nullptr),
        mesh(nullptr), shape(nullptr) { }
};

VSRAY_NAMESPACE_END
