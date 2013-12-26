#pragma once

#include "core/vsray.hpp"
#include "core/intersection.hpp"
#include "core/primitive.hpp"
#include "core/light.hpp"

VSRAY_NAMESPACE_BEGIN

class Scene {
public:
    Primitive *primitive;
    vector<Light *> lights;

    Scene(Primitive *primitive, const vector<Light *> &lights);
    ~Scene();

    virtual bool intersect(const Ray &ray, Intersection *is) const;
};

VSRAY_NAMESPACE_END
