#pragma once

#include "core/vsray.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Intersection;
class Sample;

class SurfaceIntegrator {
public:
    virtual Spectrum radiance(Sample &sample, Intersection &is);
};

VSRAY_NAMESPACE_END

