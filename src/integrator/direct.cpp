#include "integrator/direct.hpp"
#include "core/bsdf.hpp"
#include "core/intersection.hpp"
#include "core/light.hpp"
#include "core/mcmc.hpp"
#include "core/ray.hpp"
#include "core/render.hpp"
#include "core/sample.hpp"
#include "core/scene.hpp"
#include "shape/mesh.hpp"

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

    // // shadow ray
    Ray ray(is.p, wi, maxT);
    if (scene->intersect(ray, nullptr, is.epsilon)) {
        // assert(is.shape != useless.shape);
        // const Mesh *m = (dynamic_cast<const Mesh *>(useless.shape));
        // const Mesh *m0 = (dynamic_cast<const Mesh *>(is.shape));
        // // printf("%d, %.3f\n", m->index, useless.t);
        // int t = m->index;
        // // printf("%d, %.3f\n", m->index, useless.t);
        // if (t == 15859) {
        //     printf("%.3f %.3f\n", is.u, is.v);
        //     useless.fillIntersection();
        //     pobj(*m0);
        //     pobj(is.p);
        //     pobj(*m);
        //     pobj(useless.p);
        //     pobj(wi);
        // return Spectrum(0.4f, 0.8f, 0.f);
        // }
        return ret;
    }

    assert(is.bsdf);
    Vector wo = -is.ray->d.normalize();
    Spectrum f = is.bsdf->f(wo, wi);

    // if (wi.dot(is.sn) <= 0)
    //     return Spectrum(0, 1, 1);
    if (light->isDelta()) {
        ret += f * li * clamp(wi.dot(is.sn), 0.f, 1.f) * lightPdf;
    } else {
        // bsdfPdf = is.bsdf->pdf(wo, wi);
        real weight = misPowerHeuristic(1, lightPdf, 0, 0.f);
        ret += f * li * abs(wi.dot(is.sn)) * weight / lightPdf;
    }

    // TODO  using bsdf
    // Vector ref = wo - 2.f * (wo - is.sn * wo.dot(is.sn));
    // real vdot = ref.dot(is.ray->d);
    // if (vdot < 0)
    //     ret += f * li * powf(-vdot, 50.f) / lightPdf;

    return ret;
    // TODO add BSDF sample: for reflectance
}

VSRAY_NAMESPACE_END
