#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

// return [low, high)
Float nextRandomFloat(Float low = 0.f, Float high = 1.f);
// return [low, high)
int nextRandomInt(int high);
int nextRandomInt(int low, int high);

VSRAY_NAMESPACE_END
