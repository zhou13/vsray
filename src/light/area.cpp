#include "light/area.hpp"
#include "core/shape.hpp"
#include "core/geometry.hpp"
#include "core/sample.hpp"
#include "core/mesh.hpp"
#include "core/mcmc.hpp"

VSRAY_NAMESPACE_BEGIN

AreaLight::AreaLight(const Shape *shape, Spectrum emit):
    shape(shape), emit(emit)
{
    // pass
}

Spectrum AreaLight::sampleL(
        const Point &obj, Vector *wi, Sample &sample, Float *pdf)
{
    int idx = sample.index;

    Point pLight;
    Mesh *m = shape->sampleMesh(sample.lightJ[idx]);
    
    Float u, v;
    uniformTriangle(sample.lightU[idx], sample.lightV[idx], &u, &v);
    *pdf = m->pdf(obj, wi, u, v);

    if (*pdf == 0)
        return Spectrum(0.f);

    Float sumProjectArea = 0.f;
    for (auto mesh: shape->meshes) {
        Float projectRatio = mesh->n.dot(*wi);
        if (projectRatio > 0)
            sumProjectArea += mesh->area * projectRatio;
    }

    *pdf *= m->area * m->n.dot(*wi) / sumProjectArea;

    return emit;
}

bool AreaLight::isPointLight()
{
    return false;
}

VSRAY_NAMESPACE_END
