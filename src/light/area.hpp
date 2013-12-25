#pragma once

#include "core/light.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Shape;
class Sample;
class Point;
class Vector;

class AreaLight {
public:
    AreaLight(const Shape *shape, Spectrum emit);
    virtual Spectrum sampleL(
            const Point &obj, Vector *wi, Sample &sample, Float *pdf);
    virtual bool isPointLight();

private:
    const Shape *shape;
    Spectrum emit;
};

VSRAY_NAMESPACE_END
