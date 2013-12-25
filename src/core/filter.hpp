#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Filter {
public:
    virtual ~Filter() = 0;
    virtual Float operator() (Float dx, Float dy) = 0;
    virtual void getRange(Float *x, Float *y) = 0;
};

VSRAY_NAMESPACE_END
