#include "material/stupid.hpp"
#include "core/bsdf.hpp"
#include "bxdf/lambertian.hpp"

VSRAY_NAMESPACE_BEGIN

shared_ptr<BSDF> StupidMaterial::getBSDF(Intersection *is)
{
    shared_ptr<BSDF> b(make_shared<BSDF>(is));
    b->addBxDF(new Lambertian(Spectrum(1.f)));
    return b;
}

VSRAY_NAMESPACE_END
