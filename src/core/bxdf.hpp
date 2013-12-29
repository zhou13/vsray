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
            real u,
            real v,
            real *pdf) = 0;
    virtual real pdf(const Vector &wo, const Vector &wi) = 0;
};

VSRAY_NAMESPACE_END
