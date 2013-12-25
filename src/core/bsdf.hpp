#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;

class BSDF {
public:
    Spectrum f(const Vector &wo, const Vector &wi) = 0;
    Spectrum sampleF(
            const Vector &wo,
            const Vector *wi,
            Sample &sample,
            Float *pdf) = 0;
};

VSRAY_NAMESPACE_END
