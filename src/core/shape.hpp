#pragma once

#include "core/vsray.hpp"
#include "core/geometry.hpp"
#include "core/bbox.hpp"
#include "core/ray.hpp"
#include "core/mesh.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

class Shape {
public:
    vector<Mesh *> meshes;

    size_t size() {
        return meshes.size();
    }

    BBox getBBox() {
        BBox box;
        for (auto m: meshes)
            box = box.merge(m->getBBox());
        return box;
    }

    bool intersect(const Ray &ray, Intersection *is) {
        for (auto m: meshes) {
            if (m->intersect(ray, is)) {
                is->shape = this;
                return true;
            }
        }
        return false;
    }

    virtual bool getSurface(Intersection *is) = 0;

protected:
    object_pool<Mesh> pool;
};

VSRAY_NAMESPACE_END
