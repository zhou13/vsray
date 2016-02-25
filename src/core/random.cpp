#include "core/random.hpp"
#include <random>

VSRAY_NAMESPACE_BEGIN

Random::Random() : gen(rd())
{
    // pass
}

real Random::nextRandomReal()
{
    std::uniform_real_distribution<real> dis(0.f, 1.f);
    return (real)dis(gen);
}

real Random::nextRandomReal(real high)
{
    std::uniform_real_distribution<real> dis(0.f, high);
    return (real)dis(gen);
}

real Random::nextRandomReal(real low, real high)
{
    std::uniform_real_distribution<real> dis(low, high);
    return (real)dis(gen);
}

int Random::nextRandomInt(int high)
{
    std::uniform_int_distribution<int> dis(0, high-1);
    return dis(gen);
}

int Random::nextRandomInt(int low, int high)
{
    std::uniform_int_distribution<int> dis(low, high-1);
    return dis(gen);
}

VSRAY_NAMESPACE_END
