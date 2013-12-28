#pragma once

#include "core/vsray.hpp"
#include "core/sampler.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;

class StratifiedSampler : public Sampler {
public:
    StratifiedSampler(
            int imageWidth,
            int imageHeight,
            int nSamplePerPixel,
            int nLight,
            int nBSDF,
            bool stratified);
    virtual ~StratifiedSampler();

    virtual Sampler *duplicate();
    virtual void initialize(int x0, int x1, int y0, int y1);
    virtual bool genSamples(Sample *samples, int *n);
    virtual int getSamplesCount();
    virtual int roundSize(int size);

private:
    int imageWidth, imageHeight;
    int x0, x1, y0, y1, width, height;
    int nSamplePerPixel;
    bool stratified;

    int numSamples;
    int numSamplesLeft;

    Float *imageX, *imageY;
    Float *lensU, *lensV;

    bool initialized;

    Float offset();
    void genStratified1D(Float **f, int n);
};

VSRAY_NAMESPACE_END
