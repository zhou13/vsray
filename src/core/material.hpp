#pragma once
#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class BSDF;
class Intersection;

// BxDF + Texture = Material
class Material {
public:
    virtual shared_ptr<BSDF> getBSDF(Intersection *is) = 0;
};

VSRAY_NAMESPACE_END
