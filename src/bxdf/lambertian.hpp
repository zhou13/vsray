#pragma once

#include "core/vsray.hpp"
#include "core/spectrum.hpp"
#include "core/bxdf.hpp"

VSRAY_NAMESPACE_BEGIN

class Lambertian : public BxDF {
public:
    Lambertian(Spectrum r);
    virtual Spectrum f(const Vector &wo, const Vector &wi);
    virtual Spectrum sampleF(
            const Vector &wo,
            Vector *wi,
            Float u,
            Float v,
            Float *pdf);
    virtual Float pdf(const Vector &wo, const Vector &wi);
private:
    Spectrum r, invR;
};

VSRAY_NAMESPACE_END
