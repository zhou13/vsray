#pragma once

#include "core/camera.hpp"

VSRAY_NAMESPACE_BEGIN

class OrthoCamera : public Camera {
public:
    OrthoCamera(
            const Point &from,
            const Vector &to,
            const Vector &up,
            real width,
            real height);
    virtual void genRay(const Sample &sample, Ray *ray);

private:
    real width;
    real height;
};

VSRAY_NAMESPACE_END
