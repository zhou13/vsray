#include "core/vsray.hpp"
#include "core/film.hpp"
#include "core/scene.hpp"
#include "core/surface-integrator.hpp"

#include <atomic>

VSRAY_NAMESPACE_BEGIN

class Render {
public:
    Render(Scene *scene, Film *film, SurfaceIntegrator *si);

    void run();
    void subtaskRun();

private:
    Scene *scene;
    Film *film;
    SurfaceIntegrator *si;
    int width, height;

    vector<std::pair<int, int>> patchQueue;
    std::atomic_int globalIndex;
};

VSRAY_NAMESPACE_END
