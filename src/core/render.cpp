#include "core/render.hpp"
#include "core/sample.hpp"
#include "core/camera.hpp"

#include <thread>

VSRAY_NAMESPACE_BEGIN

const int PATCH_SIZE = 100;

Render::Render(
        Scene *scene, Film *film, Sampler *sampler, SurfaceIntegrator *si) :
    scene(scene), film(film), sampler(sampler), si(si)
{
    width = film->width;
    height = film->height;
}

void Render::run()
{
    int cntW = (width-1) / PATCH_SIZE + 1;
    int cntH = (height-1) / PATCH_SIZE + 1;
    for (int i = 0; i < cntW; ++i)
        for (int j = 0; j < cntH; ++j)
            patchQueue.push_back(std::make_pair(
                            PATCH_SIZE * i, PATCH_SIZE * j));

    std::random_shuffle(patchQueue.begin(), patchQueue.end());

    int numThread = std::thread::hardware_concurrency();
    vector<std::thread> threads;

    globalIndex = 0;
    for (int i = 0; i < numThread; ++i)
        threads.push_back(std::thread(&Render::subtaskRun, this));
    for (int i = 0; i < numThread; ++i)
        threads[i].join();
}

void Render::subtaskRun()
{
    for (;;) {
        int idx = globalIndex++;
        if (idx >= (int)patchQueue.size())
            return;

        Sampler *subSampler = sampler->duplicate();

        int x0 = patchQueue[idx].first;
        int y0 = patchQueue[idx].second;
        int x1 = std::min(x0 + PATCH_SIZE, width);
        int y1 = std::min(y0 + PATCH_SIZE, height);

        subSampler->initialize(x0, x1, y0, y1);
        Sample *samples = new Sample[subSampler->getSamplesCount()];
        int n;

        while (sampler->genSamples(samples, &n))
            for (int i = 0; i < n; ++i) {
                Ray ray;
                scene->camera->genRay(samples[i], &ray);
                film->addSample(samples[i], raytrace(samples[i], ray));
            }

        delete samples;
        delete subSampler;
    }
}

Spectrum Render::raytrace(Sample &sample, const Ray& ray)
{
    Intersection is;
    if (scene->primitive->intersect(ray, &is))
        return si->radiance(sample, is);
    return Spectrum(0.f);
}

VSRAY_NAMESPACE_END
