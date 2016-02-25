#pragma once

#include "core/primitive.hpp"
#include "core/transform.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Shape;
class Intersection;

class TransformPrimitive : public Primitive {
public:
    TransformPrimitive(const Primitive *primitive, const Transform &objectToWorld);
    virtual BBox getBBox() const;
    virtual bool intersect(const Ray &ray, Intersection *is, real epilson) const;

private:
    const Primitive *primitive;
    Transform objectToWorld, worldToObject;
};

VSRAY_NAMESPACE_END
