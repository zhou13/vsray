#pragma once

#include "core/vsray.hpp"
#include "core/sampler.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;

class StratifiedSampler : public Sampler {
public:
    StratifiedSampler(
            int imageWidth, int imageHeight,
            int x0, int x1, int y0, int y1, // x0 <= x < x1
            int nSample, bool stratified);
    ~StratifiedSampler();

    virtual bool genSamples(Sample *samples, int *n);
    virtual int getSamplesCount();
    virtual int roundSize(int size);

private:
    int imageWidth, imageHeight;
    int x0, x1, y0, y1, width, height;
    int nSample;
    bool stratified;

    int numSamples;
    int numSamplesLeft;

    Float *imageX, *imageY;
    Float *lensU, *lensV;

    Float offset();
    void genStratified1D(Float *f, int n);

};

VSRAY_NAMESPACE_END
