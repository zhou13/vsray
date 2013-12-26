#include "core/shape.hpp"
#include "core/geometry.hpp"
#include "core/bbox.hpp"
#include "core/ray.hpp"
#include "core/mesh.hpp"
#include "core/intersection.hpp"
#include "core/mcmc.hpp"

VSRAY_NAMESPACE_BEGIN

Mesh *Shape::samplePoint(Float w, Float u, Float v, Point *p) const
{
    int index = int((Float)size() * w);
    uniformTriangle(u, v, &u, &v);
    *p = meshes[index]->uvToPoint(u, v);
    return meshes[index];
}

size_t Shape::size() const
{
    return meshes.size();
}

bool Shape::intersect(const Ray &ray, Intersection *is) const
{
    for (auto m: meshes) {
        if (m->intersect(ray, is))
            return true;
    }
    return false;
}

VSRAY_NAMESPACE_END