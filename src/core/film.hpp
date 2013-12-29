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
    Film(int width, int height, Filter *filter, string filename);
    ~Film();
    void addSample(const Sample &sample, Spectrum sp);
    void saveToDisk();
    int width, height;

private:
    Pixel *image;
    Filter *filter;
    Float dx, dy;
    string filename;

    Float clamp(Float v, Float min, Float max);
};

VSRAY_NAMESPACE_END
