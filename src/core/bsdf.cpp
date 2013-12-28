#include "core/bsdf.hpp"
#include "core/intersection.hpp"
#include "core/bxdf.hpp"
#include "core/mesh.hpp"
#include "core/sample.hpp"

VSRAY_NAMESPACE_BEGIN

BSDF::BSDF(const Intersection *is) :
    ex(), ey(), ez(is->sn)
{
    ez = is->sn;
    ex = (is->mesh->a - is->mesh->b).normalize();
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

Vector BSDF::worldToSurface(const Vector &v) const
{
    return Vector(v.dot(ex), v.dot(ey), v.dot(ez));
}

Vector BSDF::surfaceToWorld(const Vector &v) const
{
    return Vector(ex * v.x + ey * v.y + ez * v.z);
}

Float BSDF::pdf(const Vector &wo, const Vector &wi) const
{
    Float p;
    for (auto b: bxdfs)
        p += b->pdf(wo, wi);
    return p / (Float)bxdfs.size();
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
        Float *pdf) const
{
    Vector wo = worldToSurface(wo_);

    int idx = sample.index;
    int k = int(sample.bxdfI[idx] * (Float)bxdfs.size());
    bxdfs[k]->sampleF(wo, wi, sample.bxdfU[idx], sample.bxdfV[idx], nullptr);

    Spectrum f;
    *pdf = 0;
    for (auto b: bxdfs) {
        f += b->f(wo, *wi);
        *pdf += b->pdf(wo, *wi);
    }
    *pdf /= (Float)bxdfs.size();
    return f;
}

VSRAY_NAMESPACE_END
