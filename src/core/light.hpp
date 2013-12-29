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
            const Point &obj,
            Vector *wi,
            real *len,
            Sample &sample,
            real *pdf) = 0;
    virtual bool isDelta() = 0;
    virtual ~Light() { }
};

VSRAY_NAMESPACE_END
