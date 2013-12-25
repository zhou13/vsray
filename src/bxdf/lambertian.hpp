#pragma once

#include "core/vsray.hpp"
#include "core/spectrum.hpp"
#include "core/bxdf.hpp"

VSRAY_NAMESPACE_BEGIN

class Lambertian : public BxDF {
public:
    Lambertian(Spectrum r);
    virtual Spectrum f(const Vector &wo, const Vector &wi) = 0;
    virtual Spectrum sampleF(
            const Vector &wo,
            Vector *wi,
            Float u,
            Float v,
            Float *pdf) = 0;
private:
    Spectrum r, invR;
};

VSRAY_NAMESPACE_END
