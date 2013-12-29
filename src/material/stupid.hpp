#pragma once

#include "core/material.hpp"
#include "core/spectrum.hpp"

VSRAY_NAMESPACE_BEGIN

// quick and dirty Lambertian without texture
class StupidMaterial : public Material {
public:
    StupidMaterial(Spectrum sp = Spectrum(1.f));
    virtual shared_ptr<BSDF> getBSDF(Intersection *is);
private:
    Spectrum sp;
};

VSRAY_NAMESPACE_END

