#pragma once

#include "core/texture.hpp"

VSRAY_NAMESPACE_BEGIN

template <typename T>
class ConstantTexture : public Texture<T> {
public:
    ConstantTexture() { }
    ConstantTexture(const T &value) : value(value) { }
    virtual T evaluate(const Intersection &) {
        return value;
    }

private:
    T value;
};

VSRAY_NAMESPACE_END
