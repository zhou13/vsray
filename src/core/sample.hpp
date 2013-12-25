#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample {
public:
    Float imageX, imageY;
    Float lensU, lensV;

    Float *lightU, *lightV, *lightI, *lightJ;
    Float *bxdfU, *bxdfV, *bxdfI;

    int nSample, index;

    Sample(int nSample = 0): nSample(nSample), index(0) {
        lightU = new Float[nSample];
        lightV = new Float[nSample];
        lightI = new Float[nSample];
        lightJ = new Float[nSample];
        bxdfU = new Float[nSample];
        bxdfV = new Float[nSample];
        bxdfI = new Float[nSample];
    }

    ~Sample() {
        delete[] lightU;
        delete[] lightV;
        delete[] lightI;
        delete[] lightJ;
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
