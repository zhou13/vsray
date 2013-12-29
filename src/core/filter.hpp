#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Filter {
public:
    real size;
    Filter(real size): size(size) { }
    virtual real operator()(real x, real y) = 0;
    virtual ~Filter() { }
};

VSRAY_NAMESPACE_END
