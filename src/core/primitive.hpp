#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Primitive {
public:
    virtual bool intersect(const Ray &ray, Intersection *is) const = 0;
};

VSRAY_NAMESPACE_END
