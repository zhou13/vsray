#pragma once

#include "core/meshset.hpp"

VSRAY_NAMESPACE_BEGIN

class UVSphere : public Meshset {
public:
    UVSphere(
            const Point &center,
            Float radius,
            int cntU,
            int cntV,
            bool inter,
            object_pool<Mesh> *pool
    );
};

VSRAY_NAMESPACE_END
