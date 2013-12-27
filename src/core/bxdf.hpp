#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Vector;

class BxDF {
public:
    virtual ~BxDF() { };
    virtual Spectrum f(const Vector &wo, const Vector &wi) = 0;
    virtual Spectrum sampleF(
            const Vector &wo,
            Vector *wi,
            Float u,
            Float v,
            Float *pdf) = 0;
    virtual Float pdf(const Vector &wo, const Vector &wi) = 0;
};

VSRAY_NAMESPACE_END
