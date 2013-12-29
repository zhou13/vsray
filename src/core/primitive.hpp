#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Intersection;

class Primitive {
public:
    virtual ~Primitive() { }
    virtual bool intersect(
            const Ray &ray, Intersection *is, Float epsilon) const = 0;
};

VSRAY_NAMESPACE_END
