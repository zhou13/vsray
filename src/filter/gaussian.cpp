#include "filter/gaussian.hpp"

VSRAY_NAMESPACE_BEGIN

GaussianFilter::GaussianFilter(Float size, Float alpha):
    Filter(size), alpha(alpha)
{
    e2 = exp(-alpha * size * size);
}

Float GaussianFilter::operator()(Float dx, Float dy)
{
    return (exp(-alpha * dx * dx) - e2) * (exp(-alpha * dy * dy) - e2);
}

VSRAY_NAMESPACE_END
