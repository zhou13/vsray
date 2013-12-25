#include "bxdf/lambertian.hpp"
#include "core/mcmc.hpp"

Lambertian::Lambertian(Spectrum r): r(r)
{
    // pass
}

Spectrum Lambertian::f(const Vector &wo, const Vector &wi)
{
    // We have to divided it by a PI is because the integral
    // c = Lo(wo) = \int f(wi, wo) * c * dwi
    return r * INV_PI;
}

Spectrum Lambertian::sampleF(
        const Vector &wo,
        const Vector *wi,
        Float u,
        Float v,
        Float *pdf)
{
    cosineHemisphere(u, v, wi);
    if (wo.z < 0)
        wi.z = -1.f;
    *pdf = wi.z * INV_PI;
}
