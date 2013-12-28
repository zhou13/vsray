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
        const Point &obj, Vector *wi, Float *len, Sample &sample, Float *pdf)
{
    int idx = sample.idxLight;
    Mesh *m = shape->meshes[int(Float(shape->meshes.size()) * sample.lightJ[idx])];
    
    Float u, v;
    uniformTriangle(sample.lightU[idx], sample.lightV[idx], &u, &v);

    Point p = m->uvToPoint(u, v);
    *wi = (p - obj).normalize();
    if (m->n.dot(*wi) >= 0.f)
        return 0.f;

    *len = obj.distance2(p);
    *pdf = abs(*len / (m->uvToNormal(u, v).dot(*wi) * m->area));
    if (*pdf == 0.f)
        return Spectrum(0.f);
    *len = sqrt(*len);
    *pdf *= -m->area * m->n.dot(*wi) / (Float)shape->meshes.size();

    /*
    Float sumProjectArea = 0.f;
    for (auto mesh: shape->meshes) {
        Float projectRatio = -mesh->n.dot(*wi);
        if (projectRatio > 0)
            sumProjectArea += mesh->area * projectRatio;
    }
    */

    return emit;
}

bool AreaLight::isPointLight()
{
    return false;
}

VSRAY_NAMESPACE_END
