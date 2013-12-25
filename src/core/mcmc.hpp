#pragma once

#include "core/vsray.hpp"
#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

inline void uniformDisk(Float u, Float v, Float *x, Float *y)
{
    Float r = sqrt(u);
    Float theta = 2.f * PI * v;
    *x = r * cos(theta);
    *y = r * sin(theta);
}

inline void uniformHemisphere(Float u, Float v, Vector *vec)
{
    vec->x = cos(2.f * PI * v) * sqrt(1.f - u * u);
    vec->y = sin(2.f * PI * v) * sqrt(1.f - u * u);
    vec->z = u;
}

inline void uniformTriangle(Float u, Float v, Float *uu, Float *vv)
{
    Float su = sqrt(u);
    *uu = 1.f - su;
    *vv = v * su;
}

// Malley's method
inline void cosineHemisphere(Float u, Float v, Vector *vec)
{
    uniformDisk(u, v, &vec->x, &vec->y);
    vec->z = sqrt(std::max(Float(0), 1.f - (vec->x) * (vec->x) - (vec->y) * (vec->y)));
}

inline Float misBalanceHeuristic(int cntF, Float pdfF, int cntG, Float pdfG)
{
    Float f = (Float)cntF * pdfF;
    Float g = (Float)cntG * pdfG;
    return f / (f + g);
}

inline Float misPowerHeuristic(int cntF, Float pdfF, int cntG, Float pdfG)
{
    Float f = (Float)cntF * pdfF;
    Float g = (Float)cntG * pdfG;
    return f * f / (f * f + g * g);
}

VSRAY_NAMESPACE_END
