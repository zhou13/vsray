#pragma once

#include "core/camera.hpp"

VSRAY_NAMESPACE_BEGIN

class OrthoCamera : public Camera {
public:
    OrthoCamera(
            const Point &from,
            const Vector &to,
            const Vector &up,
            Float width,
            Float height);
    virtual void genRay(const Sample &sample, Ray *ray);

private:
    Float width;
    Float height;
};

VSRAY_NAMESPACE_END
