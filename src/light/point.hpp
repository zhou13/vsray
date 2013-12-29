#pragma once

#include "core/light.hpp"
#include "core/geometry.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;
class Vector;

class PointLight : public Light {
public:
    PointLight(const Point &o, Spectrum intensity);
    virtual Spectrum sampleL(
            const Point &obj, Vector *wi, real *len, Sample &sample, real *pdf);
    virtual bool isDelta();

private:
    Point o;
    Spectrum intensity;
};

VSRAY_NAMESPACE_END

