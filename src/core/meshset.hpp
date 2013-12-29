#pragma once

#include "core/bbox.hpp"
#include "core/vsray.hpp"
#include "core/primitive.hpp"

VSRAY_NAMESPACE_BEGIN

class Ray;
class Mesh;
class Intersection;

class Meshset : public Primitive {
public:
    Mesh *operator[](int index);
    size_t size() const;
    void addMesh(Mesh *m);
    virtual bool intersect(const Ray &ray, Intersection *is, Float epsilon) const;
    virtual BBox getBBox() const;

private:
    vector<Mesh *> meshes;
};

VSRAY_NAMESPACE_END
