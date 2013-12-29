#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Random {
public:
    Random();
    Float nextRandomFloat();
    Float nextRandomFloat(Float high);
    Float nextRandomFloat(Float low, Float high);
    int nextRandomInt(int high);
    int nextRandomInt(int low, int high);

private:
    std::random_device rd;
    std::mt19937 gen;
};

VSRAY_NAMESPACE_END
