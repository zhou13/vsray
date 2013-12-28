#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample {
public:
    Float imageX, imageY;
    Float lensU, lensV;

    Float *lightU, *lightV, *lightI, *lightJ;
    Float *bxdfU, *bxdfV, *bxdfI;

    int nLight, nBSDF, idxLight, idxBSDF;

    Sample()
    {
        nLight = nBSDF = idxLight = idxBSDF = 0;
        lightU = nullptr;
        lightV = nullptr;
        lightI = nullptr;
        lightJ = nullptr;
        bxdfU = nullptr;
        bxdfV = nullptr;
        bxdfI = nullptr;
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
