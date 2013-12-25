#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

void uniformUVSphere(Float u, Float v, Float *phi, Float *theta);
void uniformDisk(Float u, Float v, Float *r, Float *theta);

class Sample;

class Sampler {
public:
    virtual bool genSamples(Sample *samples, int *n) = 0;
    virtual int getSamplesCount() = 0;
    virtual int roundSize(int size) = 0;
};

VSRAY_NAMESPACE_END
