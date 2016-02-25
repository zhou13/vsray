#pragma once

#include "core/material.hpp"
#include "core/spectrum.hpp"
#include "core/texture.hpp"

VSRAY_NAMESPACE_BEGIN

// quick and dirty Lambertian without texture
class StupidMaterial : public Material {
public:
    StupidMaterial(shared_ptr<Texture<Spectrum>> color);
    virtual shared_ptr<BSDF> getBSDF(Intersection &is) const;

private:
    shared_ptr<Texture<Spectrum>> color;
};

VSRAY_NAMESPACE_END

