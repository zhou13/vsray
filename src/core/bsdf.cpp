#include "core/bsdf.hpp"
#include "core/bxdf.hpp"
#include "core/intersection.hpp"
#include "core/sample.hpp"

VSRAY_NAMESPACE_BEGIN

BSDF::BSDF(const Intersection &is) :
    ex(), ey(), ez(is.sn)
{
    ez = is.sn;
    ex = is.ta;
    ey = ez.cross(ex);
}

BSDF::~BSDF()
{
    for (auto b: bxdfs)
        delete b;
}

void BSDF::addBxDF(BxDF *bxdf)
{
    bxdfs.push_back(bxdf);
}

inline Vector BSDF::worldToSurface(const Vector &v) const
{
    return Vector(v.dot(ex), v.dot(ey), v.dot(ez));
}

inline Vector BSDF::surfaceToWorld(const Vector &v) const
{
    return Vector(ex * v.x + ey * v.y + ez * v.z);
}

real BSDF::pdf(const Vector &wo, const Vector &wi) const
{
    real p = 0.f;
    for (auto b: bxdfs)
        p += b->pdf(wo, wi);
    return p / (real)bxdfs.size();
}

Spectrum BSDF::f(const Vector &wo_, const Vector &wi_) const
{
    Vector wo = worldToSurface(wo_);
    Vector wi = worldToSurface(wi_);

    Spectrum f;
    for (auto b: bxdfs)
        f += b->f(wo, wi);
    return f;
}

Spectrum BSDF::sampleF(
        const Vector &wo_,
        Vector *wi,
        Sample &sample,
        real *pdf) const
{
    Vector wo = worldToSurface(wo_);

    int idx = sample.idxBSDF;
    int k = int(sample.bxdfI[idx] * (real)bxdfs.size());
    bxdfs[k]->sampleF(wo, wi, sample.bxdfU[idx], sample.bxdfV[idx], nullptr);

    Spectrum f;
    *pdf = 0;
    for (auto b: bxdfs) {
        f += b->f(wo, *wi);
        *pdf += b->pdf(wo, *wi);
    }
    *pdf /= (real)bxdfs.size();
    return f;
}

VSRAY_NAMESPACE_END
