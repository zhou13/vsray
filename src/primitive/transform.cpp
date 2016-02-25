#include "primitive/transform.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

TransformPrimitive::TransformPrimitive(
        const Primitive *primitive,
        const Transform &objectToWorld) :
    primitive(primitive),
    objectToWorld(objectToWorld),
    worldToObject(objectToWorld.inverse())
{
    // pass
}

BBox TransformPrimitive::getBBox() const
{
    return objectToWorld(primitive->getBBox());
}

bool TransformPrimitive::intersect(const Ray &ray, Intersection *is, real epsilon) const
{
    Ray ray2 = worldToObject(ray);
    if (primitive->intersect(ray2, is, epsilon)) {
        ray.maxT = ray2.maxT;
        if (is)
            is->transform = &objectToWorld;
        return true;
    }
    return false;
}

VSRAY_NAMESPACE_END
