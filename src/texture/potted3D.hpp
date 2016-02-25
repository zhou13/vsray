#pragma once

#include "core/texture.hpp"
#include "core/random.hpp"
#include "core/geometry.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

const real SIZE = 2;

template <typename T>
class Potted3DTexture : public Texture<T> {
public:
    Potted3DTexture(real r, int cnt, const T &val0, const T &val1) :
        r2(r*r), val0(val0), val1(val1)
    {
        for (int t = 0; t < cnt; ++t) {
            Point p(rand.nextRandomReal(SIZE),
                    rand.nextRandomReal(SIZE),
                    rand.nextRandomReal(SIZE));
            bool ok = true;
            for (auto &p1: vec)
                if (p.distance2(p1) < 4*r2)
                    ok = false;
            if (!ok)
                continue;
            for (int i = -1; i <= 1; ++i)
                for (int j = -1; j <= 1; ++j)
                    for (int k = -1; k <= 1; ++k)
                        vec.push_back(Point(p.x + SIZE * i,
                                            p.y + SIZE * j,
                                            p.z + SIZE * k));
        }
    }

    virtual T evaluate(const Intersection &is) {
        real x = tile(is.p.x, SIZE);
        real y = tile(is.p.y, SIZE);
        real z = tile(is.p.z, SIZE);

        Point p0(x, y, z);
        for (auto &p: vec)
            if (p.distance2(p0) < r2)
                return val1;
        return val0;
    }

private:
    real r2;
    T val0, val1;
    vector<Point> vec;
    Random rand;
};

VSRAY_NAMESPACE_END
