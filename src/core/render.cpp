#include "core/render.hpp"
#include "core/sample.hpp"
#include "core/camera.hpp"
#include "core/ray.hpp"

#include <thread>

VSRAY_NAMESPACE_BEGIN

const int PATCH_SIZE = 200;

Render::Render(
        Scene *scene,
        Film *film,
        Sampler *sampler,
        SurfaceIntegrator *si,
        uint32_t maxThread) :
    scene(scene), film(film), sampler(sampler), si(si), maxThread(maxThread)
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

    int numThread = std::min(std::thread::hardware_concurrency(), maxThread);
    if (numThread == 0) {
        printf("Warning: unable to detect the number of physical core\n");
        printf("Fallback to single core mode\n");
        numThread = 1;
    }
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
        printf("pitch: %d\n", idx);

        int x0 = patchQueue[idx].first;
        int y0 = patchQueue[idx].second;
        int x1 = std::min(x0 + PATCH_SIZE, width);
        int y1 = std::min(y0 + PATCH_SIZE, height);

        Sampler *subSampler = sampler->duplicate();
        subSampler->initialize(x0, x1, y0, y1);

        Sample *samples = new Sample[subSampler->getSamplesCount()];
        int n;

        for (;;) {
            bool b = subSampler->genSamples(samples, &n);
            for (int i = 0; i < n; ++i) {
                Ray ray;
                scene->camera->genRay(samples[i], &ray);
                film->addSample(samples[i], raytrace(samples[i], ray));
            }
            if (!b)
                break;
        }

        film->saveToDisk();

        delete[] samples;
        delete subSampler;
    }
}

Spectrum Render::raytrace(Sample &sample, const Ray& ray)
{
    Intersection is;
    if (scene->primitive->intersect(ray, &is, 0.f)) {
        is.fillIntersection();
        assert(is.bsdf);
        Spectrum r = si->radiance(sample, is);
        return r;
    }
    return Spectrum(0.f);
}

VSRAY_NAMESPACE_END
