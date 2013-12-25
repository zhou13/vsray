#pragma once

#include "core/vsray.hpp"
#include "core/filter.hpp"

VSRAY_NAMESPACE_BEGIN

class BoxFilter : public Filter {
public:
    BoxFilter(Float size = 1.f);
    virtual Float operator()(Float dx, Float dy);
};

VSRAY_NAMESPACE_END
