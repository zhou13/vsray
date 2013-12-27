#include "bxdf/lambertian.hpp"
#include "core/mcmc.hpp"

VSRAY_NAMESPACE_BEGIN

Lambertian::Lambertian(Spectrum r): r(r), invR(r * INV_PI)
{
    // pass
}

Spectrum Lambertian::f(const Vector &, const Vector &)
{
    // We have to divided it by a PI is because the integral
    // c = Lo(wo) = \int f(wi, wo) * c * dwi
    return invR;
}

Float Lambertian::pdf(const Vector &, const Vector &wi)
{
    return abs(wi.z * INV_PI);
}

Spectrum Lambertian::sampleF(
        const Vector &wo,
        Vector *wi,
        Float u,
        Float v,
        Float *pdf_)
{
    cosineHemisphere(u, v, wi);
    if (wo.z < 0)
        wi->z = -1.f;
    if (pdf_)
        *pdf_ = pdf(wo, *wi);
    return invR;
}

VSRAY_NAMESPACE_END
