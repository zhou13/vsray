#pragma once

#include "core/vsray.hpp"
#include "core/bbox.hpp"
#include "core/mesh.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Intersection;

class Shape {
public:
    vector<Mesh *> meshes;

    size_t size() const;
    BBox getBBox() const;
    bool intersect(const Ray &ray, Intersection *is) const;
    Mesh *samplePoint(Float w, Float u, Float v, Point *p) const;

protected:
    object_pool<Mesh> pool;
};

VSRAY_NAMESPACE_END
