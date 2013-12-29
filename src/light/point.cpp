#include "light/point.hpp"
#include "shape/meshset.hpp"

VSRAY_NAMESPACE_BEGIN

PointLight::PointLight(const Point &o, Spectrum intensity) :
    o(o), intensity(intensity)
{
    // pass
}

Spectrum PointLight::sampleL(
        const Point &obj, Vector *wi, real *len, Sample &, real *pdf)
{
    Vector v = o - obj;
    *wi = v.normalize();
    *pdf = 1.f;
    *len = v.length();
    return intensity / v.length2();
}

bool PointLight::isDelta()
{
    return true;
}

VSRAY_NAMESPACE_END
