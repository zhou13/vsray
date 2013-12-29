#include "primitive/agglomerate.hpp"

VSRAY_NAMESPACE_BEGIN

void Agglomerate::addPrimitive(Primitive *p)
{
    items.push_back(p);
}

BBox Agglomerate::getBBox() const
{
    BBox box;
    for (auto p: items)
        box = box.merge(p->getBBox());
    return box;
}

bool Agglomerate::intersect(const Ray &ray, Intersection *is, real epsilon) const
{
    bool b = false;
    for (auto p: items) {
        if (p->intersect(ray, is, epsilon))
            b = true;
    }
    return b;
}

VSRAY_NAMESPACE_END

