#pragma once

#include "core/vsray.hpp"
#include "core/intersection.hpp"
#include "core/primitive.hpp"
#include "core/light.hpp"

VSRAY_NAMESPACE_BEGIN

class Camera;

class Scene {
public:
    Primitive *primitive;
    Camera *camera;
    vector<Light *> lights;

    Scene(Primitive *primitive, Camera *camera);
    Scene(Primitive *primitive, Camera *camera, const vector<Light *> &lights);

    void addLight(Light *lights);
    Light* sampleLight(Float number);
    bool intersect(const Ray &ray, Intersection *is) const;
};

VSRAY_NAMESPACE_END
