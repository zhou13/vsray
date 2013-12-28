#pragma once

#include "core/vsray.hpp"
#include "core/spectrum.hpp"
#include "core/transform.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;
class BxDF;
class Intersection;

class BSDF {
public:
    BSDF(const Intersection *is);
    ~BSDF();
    void addBxDF(BxDF *bxdf);
    Float pdf(const Vector &wo, const Vector &wi) const;
    Spectrum f(const Vector &wo, const Vector &wi) const;
    Spectrum sampleF(
            const Vector &wo,
            Vector *wi,
            Sample &sample,
            Float *pdf) const;

private:
    Vector ex, ey, ez;
    vector<BxDF *> bxdfs;
    
    Vector worldToSurface(const Vector &v) const;
    Vector surfaceToWorld(const Vector &v) const;
};

VSRAY_NAMESPACE_END
