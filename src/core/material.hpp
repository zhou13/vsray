#pragma once
#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class BSDF;
class Intersection;

// BxDF + Texture = Material
class Material {
public:
    virtual shared_ptr<BSDF> getBSDF(Intersection &is) const = 0;
    virtual ~Material() { }
};

VSRAY_NAMESPACE_END
