#pragma once

#include "core/vsray.hpp"
#include "core/geometry.hpp"

VSRAY_NAMESPACE_BEGIN

inline void uniformDisk(real u, real v, real *x, real *y)
{
    real r = sqrt(u);
    real theta = 2.f * PI * v;
    *x = r * cos(theta);
    *y = r * sin(theta);
}

inline void uniformHemisphere(real u, real v, Vector *vec)
{
    vec->x = cos(2.f * PI * v) * sqrt(1.f - u * u);
    vec->y = sin(2.f * PI * v) * sqrt(1.f - u * u);
    vec->z = u;
}

inline void uniformSphere(real u, real v, Vector *vec)
{
    vec->x = cos(2.f * PI * v) * 2 * sqrt(u - u * u);
    vec->y = sin(2.f * PI * v) * 2 * sqrt(u - u * u);
    vec->z = 1 - 2 * u;
}

inline void uniformTriangle(real u, real v, real *uu, real *vv)
{
    real su = sqrt(u);
    *uu = 1.f - su;
    *vv = v * su;
}

// Malley's method
inline void cosineHemisphere(real u, real v, Vector *vec)
{
    uniformDisk(u, v, &vec->x, &vec->y);
    vec->z = sqrt(std::max(real(0), 1.f - (vec->x) * (vec->x) - (vec->y) * (vec->y)));
}

inline real misBalanceHeuristic(int cntF, real pdfF, int cntG, real pdfG)
{
    real f = (real)cntF * pdfF;
    real g = (real)cntG * pdfG;
    return f / (f + g);
}

inline real misPowerHeuristic(int cntF, real pdfF, int cntG, real pdfG)
{
    real f = (real)cntF * pdfF;
    real g = (real)cntG * pdfG;
    return f * f / (f * f + g * g);
}

VSRAY_NAMESPACE_END
