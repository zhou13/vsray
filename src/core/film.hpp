#pragma once

#include "core/vsray.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Pixel {
public:
    Spectrum color;
    Float weight;
};

class Sample;
class Filter;

class Film {
public:
    Film(int width, int height, Filter *filter);
    ~Film();
    void addSample(const Sample &sample, Spectrum sp);
    void saveToDisk(string filename);

private:
    Pixel *image;
    Filter *filter;
    int width, height;
    Float dx, dy;

    Float clamp(Float v, Float min, Float max);
};

VSRAY_NAMESPACE_END
