#pragma once

#include "shape/meshset.hpp"

VSRAY_NAMESPACE_BEGIN

class UVSphere : public Meshset {
public:
    UVSphere(
            const Point &center,
            real radius,
            int cntU,
            int cntV,
            bool inter,
            object_pool<Mesh> *pool
    );
};

VSRAY_NAMESPACE_END
