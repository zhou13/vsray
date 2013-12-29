#pragma once

#include "core/vsray.hpp"
#include "core/filter.hpp"

VSRAY_NAMESPACE_BEGIN

class GaussianFilter : public Filter {
public:
    GaussianFilter(real size = 1.f, real alpha = 2.f);
    virtual real operator()(real dx, real dy);

private:
    real alpha;
    real e2;
};

VSRAY_NAMESPACE_END

