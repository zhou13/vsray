#include "filter/box.hpp"

VSRAY_NAMESPACE_BEGIN

BoxFilter::BoxFilter(real size): Filter(size)
{
    // pass
}

real BoxFilter::operator()(real, real)
{
    return 1.f;
}

VSRAY_NAMESPACE_END
