#pragma once

#include "core/vsray.hpp"
#include "core/shape.hpp"
#include "core/ray.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

class Primitive {
public:
    virtual ~Primitive() { }
    virtual bool intersect(const Ray &ray, Intersection *is) const = 0;
};

VSRAY_NAMESPACE_END
