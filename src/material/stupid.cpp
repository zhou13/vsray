#include "material/stupid.hpp"
#include "core/bsdf.hpp"
#include "bxdf/lambertian.hpp"

VSRAY_NAMESPACE_BEGIN

StupidMaterial::StupidMaterial(shared_ptr<Texture<Spectrum>> color) :
    color(color)
{
    // pass
}

shared_ptr<BSDF> StupidMaterial::getBSDF(Intersection &is) const
{
    shared_ptr<BSDF> b(make_shared<BSDF>(is));
    b->addBxDF(new Lambertian(color->evaluate(is)));
    return b;
}

VSRAY_NAMESPACE_END
