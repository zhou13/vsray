#pragma once

#include "core/vsray.hpp"
#include "core/transform.hpp"

VSRAY_NAMESPACE_BEGIN

class Camera {
public:
    Transform cameraToWorld;
    Point o;
    Float lensRadius;
    Float focalDistance;

    Camera(
            const Point &from,
            const Point &to,
            const Point &up
            Float lensRadius_ = 0.f,
            Float focalDistance_ = 0.f)
        : cameraToWorld(Transform.lookAt(from, to, up)), o(from),
          lensRadius(lensRadius_), focalDistance(focalDistance_) { }

    virtual void genRay(const Sample &sample, Ray *ray) = 0;

private:
    void modifyRay(Ray *ray) {
        if (lensRadius > 0) {
        }
    }
};

VSRAY_NAMESPACE_END
