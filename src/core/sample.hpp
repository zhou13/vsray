#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample {
public:
    Float imageX, imageY;
    Float lenU, lenV;

    int32_t nLight;
    Float *lightU, *lightV;
    int32_t nBxDF;
    Float *bxdfU, *bxdfV;
};

VSRAY_NAMESPACE_END
