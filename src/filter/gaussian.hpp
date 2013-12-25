#pragma once

#include "core/vsray.hpp"
#include "core/filter.hpp"

VSRAY_NAMESPACE_BEGIN

class GaussianFilter : public Filter {
public:
    GaussianFilter(Float size = 1.f, Float alpha = 2.f);
    virtual Float operator()(Float dx, Float dy);

private:
    Float alpha;
    Float e2;
};

VSRAY_NAMESPACE_END

