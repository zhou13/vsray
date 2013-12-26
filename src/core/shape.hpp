#pragma once

#include "core/bbox.hpp"
#include "core/intersection.hpp"
#include "core/mesh.hpp"
#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;

class Shape {
public:
    vector<Mesh *> meshes;

    Mesh *samplePoint(Float w, Float u, Float v, Point *p) const;
    size_t size() const;

    virtual bool intersect(const Ray &ray, Intersection *is) const;

protected:
    object_pool<Mesh> pool;
};

VSRAY_NAMESPACE_END
