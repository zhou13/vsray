#include "shape/meshset.hpp"
#include "shape/mesh.hpp"
#include "core/bbox.hpp"
#include "core/ray.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

Mesh *Meshset::operator[](int index) const
{
    return meshes[index];
}

size_t Meshset::size() const
{
    return meshes.size();
}

void Meshset::addMesh(Mesh *m)
{
    meshes.push_back(m);
}

BBox Meshset::getBBox() const
{
    BBox box;
    for (auto m: meshes)
        box = box.merge(m->getBBox());
    return box;
}

bool Meshset::intersect(const Ray &ray, Intersection *is, real epsilon) const
{
    for (auto m: meshes) {
        if (m->intersect(ray, is, epsilon))
            return true;
    }
    return false;
}

VSRAY_NAMESPACE_END
