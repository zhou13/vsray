#include "integrator/direct.hpp"
#include "core/light.hpp"
#include "core/scene.hpp"
#include "core/sample.hpp"
#include "core/render.hpp"
#include "core/intersection.hpp"
#include "core/bsdf.hpp"

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
        int &i = sample.index;
        for (i = 0; i < sample.nSample; ++i)
            r += directIllumination(
                    scene->sampleLight(sample.lightI[i]),
                    sample, is);

        r *= (Float)scene->lights.size() / (Float)sample.nSample;
    } else {
        for (Light *light: scene->lights) {
            int &i = sample.index;
            for (i = 0; i < sample.nSample; ++i)
                r += directIllumination(light, sample, is);
        }
        r /= (Float)sample.nSample;
    }
    return r;
}

Spectrum DirectIntegrator::directIllumination(
        Light *light, Sample &sample, Intersection &is)
{
    Vector wo;
    Float lPdf, fPdf;

    Spectrum l = light->sampleL(is.p, &wo, sample, &lPdf);
    Ray ray(is.p, wo);

    if (light->isPointLight()) {
        // TODO
    } else {
        Vector wi = -is.ray->d.normalize();
        Spectrum f = is.bsdf->f(wo, wi);
        fPdf = is.bsdf->pdf(wo, wi);

    }
}

VSRAY_NAMESPACE_END
