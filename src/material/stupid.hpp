#pragma once

#include "core/material.hpp"

VSRAY_NAMESPACE_BEGIN

class BSDF;
class Intersection;

// BxDF + Texture = Material
class StupidMaterial {
public:
    virtual shared_ptr<BSDF> getBSDF(Intersection *is);
};

VSRAY_NAMESPACE_END

