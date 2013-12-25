#include "core/sampler.hpp"

VSRAY_NAMESPACE_BEGIN

void uniformUVSphere(Float u, Float v, Float *phi, Float *theta)
{
    *theta = acos(u);
    *phi = 2.f * PI * v;
}

void uniformDisk(Float u, Float v, Float *r, Float *theta)
{
    *r = sqrt(u);
    *theta = 2.f * PI * v;
}

VSRAY_NAMESPACE_END
