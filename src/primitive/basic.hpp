#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class MaterialPrimitive : Primitive {
public:
    virtual bool intersect(const Ray &ray, Intersection *is) const = 0;

private:
    BSDF *bsdf;
    Light *light;
    Primitive *Primitive;
};

VSRAY_NAMESPACE_END
