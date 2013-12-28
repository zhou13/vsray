#include "core/vsray.hpp"
#include "core/surface-integrator.hpp"

VSRAY_NAMESPACE_BEGIN

class Scene;
class Render;
class Light;

class DirectIntegrator : public SurfaceIntegrator {
public:
    DirectIntegrator(Scene *scene, bool sampleLight);
    void setRender(Render *render);
    virtual Spectrum radiance(Sample &sample, Intersection &is);

private:
    Scene *scene;
    Render *render;
    bool sampleLight;

    Spectrum directIllumination(
            Light *light, Sample &sample, Intersection &is);
};

VSRAY_NAMESPACE_END
