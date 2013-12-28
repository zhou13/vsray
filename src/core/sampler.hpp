#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;

class Sampler {
public:
    Sampler(int nLight, int nBSDF) : nLight(nLight), nBSDF(nBSDF) { }
    virtual ~Sampler() { }
    virtual Sampler *duplicate() = 0;

    virtual void initialize(int x0, int x1, int y0, int y1) = 0;
    virtual bool genSamples(Sample *samples, int *n) = 0;
    virtual int getSamplesCount() = 0;
    virtual int roundSize(int size) = 0;

    int nLight, nBSDF;
};

VSRAY_NAMESPACE_END
