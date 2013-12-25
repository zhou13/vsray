#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample {
public:
    Float imageX, imageY;
    Float lensU, lensV;

    int nLight;
    Float *lightU, *lightV;
    Float *bxdfU, *bxdfV, *bxdfI;

    Sample(int nLight = 0): nLight(nLight) {
        lightU = new Float[nLight];
        lightV = new Float[nLight];
        bxdfU = new Float[nLight];
        bxdfV = new Float[nLight];
        bxdfI = new Float[nLight];
    }

    ~Sample() {
        delete[] lightU;
        delete[] lightV;
        delete[] bxdfU;
        delete[] bxdfV;
        delete[] bxdfI;
    }

    string toString() {
        return "(" +
            lexical_cast<string>(imageX) + ", " +
            lexical_cast<string>(imageY) + ")";
    }
};

VSRAY_NAMESPACE_END
