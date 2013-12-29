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
            const Point &obj, Vector *wi, Float *len, Sample &sample, Float *pdf);
    virtual bool isPointLight();

private:
    const Meshset *shape;
    Spectrum emit;
};

VSRAY_NAMESPACE_END
