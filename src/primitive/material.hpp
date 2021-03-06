#pragma once

#include "core/primitive.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Shape;
class Intersection;
class Material;

class MaterialPrimitive : public Primitive{
public:
    MaterialPrimitive(const Primitive *primitive, Material *material);
    virtual BBox getBBox() const;
    virtual bool intersect(const Ray &ray, Intersection *is, real epsilon) const;

private:
    const Primitive *primitive;
    Material *material;
};

VSRAY_NAMESPACE_END

