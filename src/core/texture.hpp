#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Intersection;

template <typename T>
class Texture {
public:
    virtual T evaluate(const Intersection &is) = 0;
    virtual ~Texture() { }
};

VSRAY_NAMESPACE_END
