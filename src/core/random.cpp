#include "core/random.hpp"
#include <random>

VSRAY_NAMESPACE_BEGIN

Random::Random() : gen(rd())
{
    // pass
}

Float Random::nextRandomFloat()
{
    std::uniform_real_distribution<Float> dis(0.f, 1.f);
    return (Float)dis(gen);
}

Float Random::nextRandomFloat(Float high)
{
    std::uniform_real_distribution<Float> dis(0.f, high);
    return (Float)dis(gen);
}

Float Random::nextRandomFloat(Float low, Float high)
{
    std::uniform_real_distribution<Float> dis(low, high);
    return (Float)dis(gen);
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
