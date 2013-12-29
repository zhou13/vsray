#include "light/area.hpp"
#include "shape/mesh.hpp"
#include "core/geometry.hpp"
#include "core/sample.hpp"
#include "core/mcmc.hpp"

#include "shape/meshset.hpp"

VSRAY_NAMESPACE_BEGIN

AreaLight::AreaLight(const Meshset *shape, Spectrum emit):
    shape(shape), emit(emit)
{
    // pass
}

Spectrum AreaLight::sampleL(
        const Point &obj, Vector *wi, real *len, Sample &sample, real *pdf)
{
    int idx = sample.idxLight;
    int meshIndex = int(real(shape->size()) * sample.lightJ[idx]);
    assert(meshIndex < (int)shape->size());
    Mesh *m = (*shape)[meshIndex];
    
    real u, v;
    uniformTriangle(sample.lightU[idx], sample.lightV[idx], &u, &v);

    Point p = m->uvToPoint(u, v);
    *wi = (p - obj).normalize();

    Normal shadeNormal = m->uvToNormal(u, v);
    if (shadeNormal.dot(*wi) >= 0.f)
        return 0.f;

    *len = obj.distance2(p);
    *pdf = abs(*len / (shadeNormal.dot(*wi) * m->area));
    if (*pdf == 0.f)
        return Spectrum(0.f);
    *len = sqrt(*len);
    *pdf *= m->area / (real)shape->size();

    /*
    real sumProjectArea = 0.f;
    for (auto mesh: shape->meshes) {
        real projectRatio = -mesh->n.dot(*wi);
        if (projectRatio > 0)
            sumProjectArea += mesh->area * projectRatio;
    }
    */

    return emit;
}

bool AreaLight::isDelta()
{
    return false;
}

VSRAY_NAMESPACE_END
