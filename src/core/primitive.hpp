#pragma once

#include "core/vsray.hpp"
#include "core/bbox.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Intersection;

class Primitive {
public:
    virtual ~Primitive() { }
    virtual BBox getBBox() const = 0;
    virtual bool intersect(
            const Ray &ray, Intersection *is, real epsilon) const = 0;
};

VSRAY_NAMESPACE_END
