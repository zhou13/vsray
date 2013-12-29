#include "primitive/adapter.hpp"

VSRAY_NAMESPACE_BEGIN

AdapterPrimitive::AdapterPrimitive(const Shape *shape) : shape(shape)
{
    // pass
}

bool AdapterPrimitive::intersect(const Ray &ray, Intersection *is, Float epsilon) const
{
    return shape->intersect(ray, is, epsilon);
}

VSRAY_NAMESPACE_END

