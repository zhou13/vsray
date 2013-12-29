#pragma once

#include "core/vsray.hpp"

VSRAY_NAMESPACE_BEGIN

const float   FLT_MAX_ABS = 5e-5f;
const int32_t FLT_MAX_ULP = 20;
const double  DBL_MAX_ABS = 1e-10;
const int32_t DBL_MAX_ULP = 40;

#ifdef DOUBLE_PRECISION
const float   FLOAT_MAX_ABS = DBL_MAX_ABS;
const int32_t FLOAT_MAX_ULP = DBL_MAX_ULP;
union float_t {
    float f;
    int64_t i;
    uint64_t u;
    struct {
        uint64_t mantissa : 52;
        uint64_t exponent : 11;
        uint64_t sign : 1;
    } s;
    float_t(Float f): f(f) { }
};
#else
const double  FLOAT_MAX_ABS = FLT_MAX_ABS;
const int32_t FLOAT_MAX_ULP = FLT_MAX_ULP;
union float_t {
    float f;
    int32_t i;
    uint32_t u;
    struct {
        uint32_t mantissa : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    };
    float_t(Float f): f(f) { }
};
#endif

inline bool float_eq(Float a, Float b)
{
    Float diff = abs(a-b);
    if (diff <= FLOAT_MAX_ABS)
        return true;

    float_t fa(a), fb(b);

    if (fa.sign != fb.sign)
        return false;

    int32_t ulpsDiff = abs(fa.i - fb.i);
    if (ulpsDiff <= FLOAT_MAX_ULP)
        return true;

    return false;
}

inline bool float_le(Float a, Float b)
{
    return a < b || float_eq(a, b);
}

inline bool float_ge(Float a, Float b)
{
    return a > b || float_eq(a, b);
}

inline bool float_eq0(Float a)
{
    return abs(a) <= FLOAT_MAX_ABS;
}

inline bool float_ge0(Float a)
{
    return a > 0 || float_eq0(a);
}

inline bool float_le0(Float a)
{
    return a < 0 || float_eq0(a);
}

VSRAY_NAMESPACE_END
