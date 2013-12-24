#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

void uniformUVSphere(Float *u, Float *v, Float *phi, Float *theta);
void uniformDisk(Float *u, Float *v, Float *phi, Float *theta);

class Sampler {
public:
}

VSRAY_NAMESPACE_END
