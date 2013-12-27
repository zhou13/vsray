#include "core/render.hpp"

#include <thread>

VSRAY_NAMESPACE_BEGIN

const int PATCH_SIZE = 100;

Render::Render(Scene *scene, Film *film, SurfaceIntegrator *si) :
    scene(scene), film(film), si(si)
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
    globalIndex
}

VSRAY_NAMESPACE_END
