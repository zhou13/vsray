#include "filter/triangle.hpp"

VSRAY_NAMESPACE_BEGIN

TriangleFilter::TriangleFilter(Float size): Filter(size)
{
    // pass
}

Float TriangleFilter::operator()(Float dx, Float dy)
{
    dx = abs(dx);
    dy = abs(dy);
    return std::max(Float(0), size - dx) * std::max(Float(0), size - dy);
}

VSRAY_NAMESPACE_END
