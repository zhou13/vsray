#pragma once

#include "core/primitive.hpp"

VSRAY_NAMESPACE_BEGIN

class Shape : public Primitive {
public:
    virtual void fillIntersection(Intersection *is) const = 0;
};

VSRAY_NAMESPACE_END
