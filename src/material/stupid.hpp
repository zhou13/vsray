#pragma once

#include "core/material.hpp"

VSRAY_NAMESPACE_BEGIN

class StupidMaterial : public Material {
public:
    virtual shared_ptr<BSDF> getBSDF(Intersection *is);
};

VSRAY_NAMESPACE_END

