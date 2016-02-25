#pragma once

#include "core/vsray.hpp"
#include "core/camera.hpp"

VSRAY_NAMESPACE_BEGIN

class PerspCamera : public Camera {
public:
    PerspCamera(
            const Transform &tr,
            real width,
            real height,
            real depth,
            real lensRadius = 0.f,
            real focalDistance = 0.f);
    PerspCamera(
            const Point &from,
            const Vector &to,
            const Vector &up,
            real width,
            real height,
            real depth,
            real lensRadius = 0.f,
            real focalDistance = 0.f);
    virtual void genRay(const Sample &sample, Ray *ray);
    void setFocalDistance(real);

private:
    void modifyRayDOF(const Sample &sample, Ray *ray);

    real width;
    real height;
    real depth;

    real lensRadius;
    real focalDistance;
};

VSRAY_NAMESPACE_END
