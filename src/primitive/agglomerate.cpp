#include "primitive/agglomerate.hpp"

VSRAY_NAMESPACE_BEGIN

void Agglomerate::addPrimitive(const Primitive *p)
{
    primitiveSet.push_back(p);
}

bool Agglomerate::intersect(const Ray &ray, Intersection *is, Float epsilon) const
{
    bool b = false;
    for (auto p: primitiveSet) {
        if (p->intersect(ray, is, epsilon))
            b = true;
    }
    return b;
}

VSRAY_NAMESPACE_END

