#include "filter/box.hpp"

VSRAY_NAMESPACE_BEGIN

BoxFilter::BoxFilter(Float size): Filter(size)
{
    // pass
}

Float BoxFilter::operator()(Float, Float)
{
    return 1.f;
}

VSRAY_NAMESPACE_END
