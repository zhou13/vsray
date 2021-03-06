#pragma once

#include "core/light.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;
class Point;
class Vector;
class Meshset;

class AreaLight : public Light {
public:
    AreaLight(const Meshset *shape, Spectrum emit);
    virtual Spectrum sampleL(
            const Point &obj, Vector *wi, real *len, Sample &sample, real *pdf);
    virtual bool isDelta();

private:
    const Meshset *shape;
    Spectrum emit;
};

VSRAY_NAMESPACE_END
