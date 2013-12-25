#include "camera/orthographic.hpp"
#include "core/sample.hpp"
#include "core/ray.hpp"

VSRAY_NAMESPACE_BEGIN

OrthoCamera::OrthoCamera(
        const Point &from,
        const Vector &to,
        const Vector &up,
        Float width,
        Float height):
    Camera(from, to, up), width(width), height(height)
{
    // pass
}

void OrthoCamera::genRay(const Sample &sample, Ray *ray)
{
    Float x = (sample.imageX - 0.5f) * width;
    Float y = (sample.imageY - 0.5f) * height;

    ray->o = cameraToWorld(Point(x, y, 0));
    ray->d = cameraToWorld(Vector(0, 0, 1));
}

VSRAY_NAMESPACE_END
