#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

class Random {
public:
    Random();
    real nextRandomreal();
    real nextRandomreal(real high);
    real nextRandomreal(real low, real high);
    int nextRandomInt(int high);
    int nextRandomInt(int low, int high);

private:
    std::random_device rd;
    std::mt19937 gen;
};

VSRAY_NAMESPACE_END
