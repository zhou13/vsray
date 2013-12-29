#pragma once

#include "core/vsray.hpp"
#include "core/filter.hpp"

VSRAY_NAMESPACE_BEGIN

class TriangleFilter : public Filter {
public:
    TriangleFilter(real size = 1.f);
    virtual real operator()(real dx, real dy);
};

VSRAY_NAMESPACE_END
