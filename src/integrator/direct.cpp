#include "integrator/direct.hpp"
#include "core/bsdf.hpp"
#include "core/intersection.hpp"
#include "core/light.hpp"
#include "core/mcmc.hpp"
#include "core/ray.hpp"
#include "core/render.hpp"
#include "core/sample.hpp"
#include "core/scene.hpp"

VSRAY_NAMESPACE_BEGIN

DirectIntegrator::DirectIntegrator(Scene *scene, bool sampleLight) :
    scene(scene), sampleLight(sampleLight)
{
}

void DirectIntegrator::setRender(Render *render_)
{
    render = render_;
}

Spectrum DirectIntegrator::radiance(Sample &sample, Intersection &is)
{
    assert(scene->lights.size() > 0);

    Spectrum r(is.radiance);
    if (sampleLight) {
        for (int i = 0; i < sample.nLight; ++i) {
            sample.idxLight = i;
            sample.idxBSDF = i;
            r += directIllumination(
                    scene->sampleLight(sample.lightI[i]),
                    sample, is);
        }
        r *= (real)scene->lights.size() / (real)sample.nLight;
    } else {
        for (Light *light: scene->lights) {
            for (int i = 0; i < sample.nLight; ++i) {
                sample.idxLight = i;
                sample.idxBSDF = i;
                r += directIllumination(light, sample, is);
            }
        }
        r /= (real)sample.nLight;
    }
    return r;
}

Spectrum DirectIntegrator::directIllumination(
        Light *light, Sample &sample, Intersection &is)
{
    Vector wi;
    real lightPdf, bsdfPdf, maxT;
    Spectrum ret(0.f);

    UNUSED(bsdfPdf);

    Spectrum li = light->sampleL(is.p, &wi, &maxT, sample, &lightPdf);
    if (lightPdf == 0)
        return ret;

    Ray ray(is.p, wi, maxT);
    // shadow ray
    // if (scene->intersect(ray, nullptr, is.epsilon))
    //     return ret;

    assert(is.bsdf);
    Vector wo = -is.ray->d.normalize();
    Spectrum f = is.bsdf->f(wo, wi);

    if (light->isDelta()) {
        ret += f * li * abs(wo.dot(is.sn)) * lightPdf;
    } else {
        // bsdfPdf = is.bsdf->pdf(wo, wi);
        real weight = misPowerHeuristic(1, lightPdf, 0, 0.f);
        ret += f * li * abs(wo.dot(is.sn)) * weight / lightPdf;
    }

    return ret;
    // TODO add BSDF sample: for reflectance
}

VSRAY_NAMESPACE_END
