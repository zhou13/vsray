#include "integrator/direct.hpp"
#include "core/bsdf.hpp"
#include "core/intersection.hpp"
#include "core/light.hpp"
#include "core/mcmc.hpp"
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
        r *= (Float)scene->lights.size() / (Float)sample.nLight;
    } else {
        for (Light *light: scene->lights) {
            for (int i = 0; i < sample.nLight; ++i) {
                sample.idxLight = i;
                sample.idxBSDF = i;
                r += directIllumination(light, sample, is);
            }
        }
        r /= (Float)sample.nLight;
    }
    return r;
}

Spectrum DirectIntegrator::directIllumination(
        Light *light, Sample &sample, Intersection &is)
{
    Vector wi;
    Float lightPdf, bsdfPdf, maxT;

    Spectrum l = light->sampleL(is.p, &wi, &maxT, sample, &lightPdf);
    Ray ray(is.p, wi, maxT);

    if (scene->intersect(ray, nullptr))
        return Spectrum(0.f);

    if (light->isPointLight()) {
        // TODO
    } else {
        assert(is.bsdf);
        Vector wo = -is.ray->d.normalize();
        Spectrum f = is.bsdf->f(wo, wi);
        // fPdf = is.bsdf->pdf(wo, wi);
        // XXX  Can we change 1 to some high number?
        return f * l * abs(wo.dot(is.sn)) * misPowerHeuristic(1, lightPdf, 0, 0.f) / lightPdf;
    }
    UNUSED(bsdfPdf);

    assert(false);
    return Spectrum(0.f);
    // TODO add BSDF sample: for reflectance
}

VSRAY_NAMESPACE_END
