#pragma once

#include "core/vsray.hpp"
#include "core/camera.hpp"

VSRAY_NAMESPACE_BEGIN

class PerspCamera : public Camera {
public:
    PerspCamera(
            const Point &from,
            const Vector &to,
            const Vector &up,
            Float width,
            Float height,
            Float depth,
            Float lensRadius = 0.f,
            Float focalDistance = 0.f);
    virtual void genRay(const Sample &sample, Ray *ray);

private:
    void modifyRayDOF(const Sample &sample, Ray *ray);

    Float width;
    Float height;
    Float depth;

    Float lensRadius;
    Float focalDistance;
};

VSRAY_NAMESPACE_END
