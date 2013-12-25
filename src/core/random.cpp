#include "core/random.hpp"
#include <random>

VSRAY_NAMESPACE_BEGIN

std::random_device *rd;
std::mt19937 *gen;

static void init()
{
    if (!rd) {
        rd = new std::random_device();
        gen = new std::mt19937((*rd)());
    }
}

Float nextRandomFloat(Float low, Float high)
{
    init();
    std::uniform_real_distribution<> dis(low, high);
    return (Float)dis(*gen);
}

int nextRandomInt(int high)
{
    init();
    std::uniform_int_distribution<> dis(0, high-1);
    return dis(*gen);
}

int nextRandomInt(int low, int high)
{
    init();
    std::uniform_int_distribution<> dis(low, high-1);
    return dis(*gen);
}



VSRAY_NAMESPACE_END
