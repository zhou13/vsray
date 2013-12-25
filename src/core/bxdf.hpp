#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class BxDF {
public:
    virtual Spectrum f(const Vector &wo, const Vector &wi) = 0;
    virtual Spectrum sampleF(
            const Vector &wo,
            const Vector &wi,
            Float u,
            Float v,
            Float *pdf) = 0;
};

VSRAY_NAMESPACE_END
