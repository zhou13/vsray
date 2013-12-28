#pragma once

#include "core/primitive.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Shape;
class Intersection;

class AdapterPrimitive : public Primitive {
public:
    AdapterPrimitive(const Shape *shape);
    virtual bool intersect(const Ray &ray, Intersection *is) const;

private:
    const Shape *shape;
};

VSRAY_NAMESPACE_END
