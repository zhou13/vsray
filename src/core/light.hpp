#pragma once

#include "core/vsray.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Point;
class Vector;
class Sample;

class Light {
public:
    virtual Spectrum sampleL(
            const Point &p, Vector *wi, Sample &sample, Float *pdf) = 0;
    virtual bool isPointLight() = 0;
};

VSRAY_NAMESPACE_END
