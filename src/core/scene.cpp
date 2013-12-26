#include "core/vsray.hpp"
#include "core/scene.hpp"
#include "core/intersection.hpp"

VSRAY_NAMESPACE_BEGIN

Scene::Scene(Primitive *primitive, const vector<Light *> &lights) :
    primitive(primitive), lights(lights)
{
}

Scene::~Scene()
{
}

bool Scene::intersect(const Ray &ray, Intersection *is) const
{
    return primitive->intersect(ray, is);
}

VSRAY_NAMESPACE_END
