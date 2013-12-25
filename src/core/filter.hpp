#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Filter {
public:
    Float size;
    Filter(Float size): size(size) { }
    virtual Float operator()(Float x, Float y) = 0;
    virtual ~Filter() { }
};

VSRAY_NAMESPACE_END
