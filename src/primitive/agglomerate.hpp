#pragma once

#include "core/primitive.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Shape;
class Intersection;

class Agglomerate : public Primitive {
public:
    void addPrimitive(Primitive *p);
    virtual BBox getBBox() const;
    virtual bool intersect(const Ray &ray, Intersection *is, real epilson) const;

protected:
    vector<Primitive *> items;
};

VSRAY_NAMESPACE_END
