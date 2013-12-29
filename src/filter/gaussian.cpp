#include "filter/gaussian.hpp"

VSRAY_NAMESPACE_BEGIN

GaussianFilter::GaussianFilter(real size, real alpha):
    Filter(size), alpha(alpha)
{
    e2 = exp(-alpha * size * size);
}

real GaussianFilter::operator()(real dx, real dy)
{
    return (exp(-alpha * dx * dx) - e2) * (exp(-alpha * dy * dy) - e2);
}

VSRAY_NAMESPACE_END
