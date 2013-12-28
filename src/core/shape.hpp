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

    Mesh *sampleMesh(Float w) const;
    Float pdf();
    size_t size() const;
    void addMesh(Mesh *m);

    bool intersect(const Ray &ray, Intersection *is) const;
    ~Shape() { }

protected:
    object_pool<Mesh> *pool;
};

VSRAY_NAMESPACE_END
