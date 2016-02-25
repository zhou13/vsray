#include "core/vsray.hpp"
#include "core/scene.hpp"
#include "core/intersection.hpp"
#include "core/camera.hpp"

VSRAY_NAMESPACE_BEGIN

Scene::Scene(Primitive *primitive, Camera *camera) :
    primitive(primitive), camera(camera)
{
    // pass
}

Scene::Scene(Primitive *primitive, Camera *camera,
             const vector<Light *> &lights) :
    primitive(primitive), camera(camera), lights(lights)
{
    // pass
}

void Scene::addLight(Light *light)
{
    lights.push_back(light);
}

void Scene::clearLight()
{
    lights.clear();
}

Light* Scene::sampleLight(real number)
{
    return lights[int(real(lights.size()) * number)];
}

bool Scene::intersect(const Ray &ray, Intersection *is, real epsilon) const
{
    return primitive->intersect(ray, is, epsilon);
}

VSRAY_NAMESPACE_END
