#include "primitive/adapter.hpp"

VSRAY_NAMESPACE_BEGIN

AdapterPrimitive::AdapterPrimitive(const Shape *shape) : shape(shape)
{
    // pass
}

bool AdapterPrimitive::intersect(const Ray &ray, Intersection *is) const
{
    return shape->intersect(ray, is);
}

VSRAY_NAMESPACE_END

