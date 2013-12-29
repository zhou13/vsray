#pragma once

#include "core/vsray.hpp"
#include "core/filter.hpp"

VSRAY_NAMESPACE_BEGIN

class BoxFilter : public Filter {
public:
    BoxFilter(real size = 1.f);
    virtual real operator()(real dx, real dy);
};

VSRAY_NAMESPACE_END
