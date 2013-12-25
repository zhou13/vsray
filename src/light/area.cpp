#include "light/area.hpp"
#include "core/shape.hpp"
#include "core/geometry.hpp"
#include "core/sample.hpp"
#include "core/mesh.hpp"

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
    Mesh *m = shape->samplePoint(
            sample.lightJ[idx],
            sample.lightU[idx],
            sample.lightV[idx],
            &pLight
    );
    *wi = (pLight - obj).normalize();
    *pdf = obj.distance2(pLight) / (
            m->uvToNormal(
                    sample.lightU[idx],
                    sample.lightV[idx]
            ).dot(*wi) * m->area()
    );
    *pdf = abs(*pdf);

    return emit;
}

bool AreaLight::isPointLight()
{
    return false;
}

VSRAY_NAMESPACE_END
