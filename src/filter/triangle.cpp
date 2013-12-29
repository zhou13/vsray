#include "filter/triangle.hpp"

VSRAY_NAMESPACE_BEGIN

TriangleFilter::TriangleFilter(real size): Filter(size)
{
    // pass
}

real TriangleFilter::operator()(real dx, real dy)
{
    dx = abs(dx);
    dy = abs(dy);
    return std::max(real(0), size - dx) * std::max(real(0), size - dy);
}

VSRAY_NAMESPACE_END
