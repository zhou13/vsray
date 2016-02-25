#pragma once

#include "core/texture.hpp"
#include "core/texture.hpp"
#include "core/random.hpp"
#include "core/geometry.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

template <typename T>
class Stratified3DTexture : public Texture<T> {
public:
    Stratified3DTexture(real len1, real len2, real len3,
                        const T &val0, const T &val1) :
        len1(len1), len2(len2), len3(len3), val0(val0), val1(val1) { }

    virtual T evaluate(const Intersection &is) {
        real x = std::fmod(is.p.x, 2 * len1);
        real y = std::fmod(is.p.y, 2 * len2);
        real z = std::fmod(is.p.z, 2 * len3);
        if (x < 0)
            x += 2 * len1;
        if (y < 0)
            y += 2 * len2;
        if (z < 0)
            z += 2 * len3;

        bool cnt = (x < len1) ^ (y < len2) ^ (z < len3);
        if (cnt)
            return val0;
        else
            return val1;
    }

private:
    real len1, len2, len3;
    T val0, val1;
};

VSRAY_NAMESPACE_END
