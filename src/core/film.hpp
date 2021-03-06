#pragma once

#include "core/vsray.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

class Pixel {
public:
    Spectrum color;
    real weight;
};

class Sample;
class Filter;

class Film {
public:
    Film(int width, int height, Filter *filter, string filename);
    ~Film();
    void addSample(const Sample &sample, Spectrum sp);
    void clear();
    void setFilename(const string &filename);
    void saveToDisk();
    int width, height;

private:
    Pixel *image;
    Filter *filter;
    real dx, dy;
    string filename;
};

VSRAY_NAMESPACE_END
