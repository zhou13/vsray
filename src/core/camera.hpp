#pragma once

#include "core/vsray.hpp"
#include "core/transform.hpp"

VSRAY_NAMESPACE_BEGIN

class Sample;
class Ray;

class Camera {
protected:
    Transform cameraToWorld;

public:
    Camera(const Point &from, const Vector &to, const Vector &up) :
        cameraToWorld(Transform::lookAt(from, to, up)) { }

    virtual void genRay(const Sample &sample, Ray *ray) = 0;
};

VSRAY_NAMESPACE_END
