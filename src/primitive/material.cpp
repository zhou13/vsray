#include "primitive/material.hpp"
#include "core/material.hpp"
#include "core/bsdf.hpp"

VSRAY_NAMESPACE_BEGIN

MaterialPrimitive::MaterialPrimitive(const Primitive *primitive, Material *material) :
    primitive(primitive), material(material)
{
    // pass
}

bool MaterialPrimitive::intersect(const Ray &ray, Intersection *is) const
{
    if (primitive->intersect(ray, is)) {
        is->bsdf = material->getBSDF(is);
        return true;
    }
    return false;
}

VSRAY_NAMESPACE_END


