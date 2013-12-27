#pragma once

#include "core/primitive.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Shape;
class Intersection;

class Agglomerate {
public:
    void addPrimitive(const Primitive *p);
    virtual bool intersect(const Ray &ray, Intersection *is) const;

private:
    vector<const Primitive *> primitiveSet;
};

VSRAY_NAMESPACE_END

