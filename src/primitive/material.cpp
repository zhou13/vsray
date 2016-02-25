#include "primitive/material.hpp"
#include "core/material.hpp"
#include "core/bsdf.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

MaterialPrimitive::MaterialPrimitive(const Primitive *primitive, Material *material) :
    primitive(primitive), material(material)
{
    // pass
}

BBox MaterialPrimitive::getBBox() const
{
    return primitive->getBBox();
}

bool MaterialPrimitive::intersect(const Ray &ray, Intersection *is, real epsilon) const
{
    if (primitive->intersect(ray, is, epsilon)) {
        if (is)
            is->material = material;
        return true;
    }
    return false;
}

VSRAY_NAMESPACE_END
